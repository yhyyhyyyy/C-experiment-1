# cpp-training 车辆指令执行器

本项目是C++课程实验工程，使用C++17、CMake和GoogleTest实现车辆指令执行与自动化测试。在基础移动和转向功能上，逐步加入加速、倒车、掉头及多车型支持，实践表驱动、函数对象、指令工厂、原子操作编排和数据驱动测试。

默认构建产物为静态库 `training` 和测试程序 `training_main`。当前测试定义包含六个测试套件、57个测试场景。

## 环境与依赖

当前批处理脚本面向Windows PowerShell与MinGW工具链，需要：

- 支持C++17的MinGW编译器。
- `mingw32-make`。
- CMake 3.13或更新版本，支持脚本中的 `-S`、`-B` 参数。
- 位于 `tests/googletest` 的GoogleTest源码。

确保工具可以从终端找到：

```powershell
cmake --version
g++ --version
mingw32-make --version
```

当前 `.gitignore` 忽略了 `tests/googletest`。如果从远端取得的工程不含该目录，需要另外准备项目使用的GoogleTest源码，其中应有 `CMakeLists.txt` 和 `googletest/include/gtest`。构建脚本不会自动下载此依赖。

## 构建与测试

在工程根目录执行：

```powershell
.\script\build_and_run.bat
```

脚本依次配置、编译、运行测试，使用 `MinGW Makefiles` 生成器。配置或编译失败时会停止，不会继续运行旧测试程序。

也可以分步操作：

```powershell
# 配置并编译
.\script\build.bat

# 仅运行上一次成功构建的测试程序
.\script\run.bat
```

修改代码后应重新构建。`run.bat` 本身不会编译。

完整测试通过时的预期汇总如下，实际结果以本机最新运行记录为准：

```text
[==========] 57 tests from 6 test suites ran.
[  PASSED  ] 57 tests.
```

成功构建后，可以列出或筛选测试：

```powershell
.\build\tests\training_main.exe --gtest_list_tests
.\build\tests\training_main.exe --gtest_filter="ExecutorTurnRoundTest.*"
.\build\tests\training_main.exe --gtest_filter="BusScenarios/*"
.\build\tests\training_main.exe --gtest_filter="SportsCarScenarios/*"
```

## 接口与使用示例

对外接口见 [Executor.hpp](include/Executor.hpp)，车型定义见 [VehicleType.hpp](include/VehicleType.hpp)。所有接口位于 `adas` 命名空间。

- `Executor::NewExecutor(pose, vehicleType)`：创建对象。默认位姿为 `(0,0,N)`，默认车型为 `VehicleType::Normal`。
- `Execute(commands)`：按顺序执行指令字符串。
- `Query()`：返回 `Pose`，其中包含 `int x`、`int y` 和 `char heading`。

N、E、S、W分别表示北、东、南、西，前进一步的位移分别为 `(0,1)`、`(1,0)`、`(0,-1)`、`(-1,0)`。

`NewExecutor` 返回的对象由调用者释放，建议使用 `std::unique_ptr`：

```cpp
#include <memory>
#include "Executor.hpp"

int main()
{
    std::unique_ptr<adas::Executor> executor(
        adas::Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) {
        return 1;
    }

    executor->Execute("FTR");
    const adas::Pose pose = executor->Query();
    // pose 为 {1, 1, 'W'}。
    return pose.x == 1 && pose.y == 1 && pose.heading == 'W' ? 0 : 1;
}
```

此代码展示接口用法；工程默认运行测试程序，没有为该示例另设应用目标。

指定其他车型时，向创建方法传入第二个参数，例如：

```cpp
std::unique_ptr<adas::Executor> bus(
    adas::Executor::NewExecutor({0, 0, 'E'}, adas::VehicleType::Bus));

std::unique_ptr<adas::Executor> sportsCar(
    adas::Executor::NewExecutor({0, 0, 'E'}, adas::VehicleType::SportsCar));
```

## 指令与状态

| 指令 | 含义 |
|---|---|
| M | 按车型和当前状态移动 |
| L | 按车型和当前状态完成左转相关动作 |
| R | 按车型和当前状态完成右转相关动作 |
| F | 切换加速状态，再次执行取消加速 |
| B | 切换倒车状态，再次执行取消倒车 |
| TR | 掉头，作为一个整体指令解析 |

F和B本身不改变位置与朝向，两个状态相互独立，并在同一对象的多次 `Execute` 调用之间保留。倒车状态下，L对应实际右转，R对应实际左转；后退不会直接改变车头朝向。

所有移动由一格的原子操作组成。连续移动两格或四格时，依次执行多个单步操作。下表中的位移均沿操作执行时的当前朝向计算。

### 普通车

| 状态 | M | L | R |
|---|---|---|---|
| 普通 | 前进1格 | 左转 | 右转 |
| B | 后退1格 | 右转 | 左转 |
| F | 前进2格 | 前进1格→左转 | 前进1格→右转 |
| BF | 后退2格 | 后退1格→右转 | 后退1格→左转 |

### 公交车

车型为 `VehicleType::Bus`。公交车占两格，位姿坐标表示车头；当前程序保存车头坐标，不另建车身占用或碰撞模型。

| 状态 | M | L | R |
|---|---|---|---|
| 普通 | 前进1格 | 前进1格→左转 | 前进1格→右转 |
| B | 后退1格 | 后退1格→右转 | 后退1格→左转 |
| F | 前进2格 | 前进2格→左转 | 前进2格→右转 |
| BF | 后退2格 | 后退2格→右转 | 后退2格→左转 |

### 跑车

车型为 `VehicleType::SportsCar`。

| 状态 | M | L | R |
|---|---|---|---|
| 普通 | 前进2格 | 左转→前进1格 | 右转→前进1格 |
| B | 后退2格 | 右转→后退1格 | 左转→后退1格 |
| F | 前进4格 | 前进1格→左转→前进1格 | 前进1格→右转→前进1格 |
| BF | 后退4格 | 后退1格→右转→后退1格 | 后退1格→左转→后退1格 |

例如跑车从 `(0,0,E)` 执行 `BFL`：先后退至 `(-1,0,E)`，再右转为S，最后沿朝南方向后退至 `(-1,1,S)`。

### TR掉头

| 状态 | 动作序列 |
|---|---|
| 普通 | 左转→前进1格→左转 |
| F | 前进1格→左转→前进1格→左转 |
| B或BF | 忽略TR，不改变位姿与状态 |

解析层将连续的 `TR` 替换为内部符号 `Z`，再通过指令表查找。用户输入仍使用 `TR`。

当前TR使用统一原子动作序列，不套用车型M、L、R的步数规则；现有三个TR测试验证默认普通车。项目按课程有效输入场景实现，不提供完整的非法输入校验。

## 目录结构

```text
cpp-training/
├─ include/
│  ├─ Executor.hpp             # 对外接口与Pose
│  └─ VehicleType.hpp          # 车型枚举
├─ src/
│  ├─ command/
│  │  ├─ Command.hpp           # 按状态与车型编排动作
│  │  ├─ CmderFactory.hpp/.cpp # 解析输入及生成命令列表
│  │  └─ ActionGroup.hpp/.cpp  # 原子操作与有序执行
│  ├─ common/
│  │  └─ Singleton.hpp         # 泛型单例入口
│  ├─ executor/
│  │  └─ ExecutorImpl.hpp/.cpp # 创建对象及执行调度
│  ├─ pose/
│  │  ├─ PoseHandler.hpp/.cpp  # 车辆位姿与状态
│  │  ├─ Point.hpp             # 坐标与位移运算
│  │  └─ Direction.hpp         # 方向与循环转向
│  ├─ CMakeLists.txt
│  └─ README.md                # 内部模块说明
├─ tests/
│  ├─ ExecutorTest.cpp
│  ├─ ExecutorFastTest.cpp
│  ├─ ExecutorReverseTest.cpp
│  ├─ ExecutorTurnRoundTest.cpp
│  ├─ ExecutorBusTest.cpp
│  ├─ ExecutorSportsCarTest.cpp
│  ├─ VehicleTestCase.hpp      # 参数化数据结构
│  ├─ PoseEq.hpp/.cpp          # 测试中的位姿比较
│  ├─ googletest/              # 本地第三方依赖
│  └─ CMakeLists.txt
├─ script/                    # Windows构建与测试脚本
├─ build/                     # 脚本使用的MinGW生成目录
├─ build-vscode/              # 编辑器独立生成目录
├─ CMakeLists.txt
└─ README.md
```

生成目录在相应构建方式运行后创建，不需要提交。CMake递归收集源文件；新增或移动 `.cpp` 后需要重新配置，构建脚本会执行这一步。

## 执行流程

1. `ExecutorImpl` 从复用的 `CmderFactory` 取得有序命令列表。
2. 工厂完成TR预处理与字符映射，此时只生成可调用对象，不提前编排全部动作。
3. 每条命令根据当时的车型、F与B状态返回 `ActionGroup`。
4. 立即执行该动作组，再处理下一条命令，保证状态切换影响后续操作。
5. 原子操作通过 `PoseHandler` 更新坐标、朝向或状态，`Query` 返回当前位姿。

八种原子操作包括前进、后退、左转、倒车左转、右转、倒车右转、切换加速和切换倒车。`ActionType` 的枚举顺序与执行表一一对应，修改时需要保持一致。

## 测试覆盖

| 类别 | 数量 | 主要场景 |
|---|---:|---|
| 基础功能 | 19 | 初始化、四向移动与转向、连续指令 |
| 加速 | 4 | FM、FL、FR、FFM |
| 倒车 | 7 | BM、BL、BR、BFM、BFL、BFR、BBM |
| 掉头 | 3 | TR、FTR、BTR |
| 公交车 | 12 | 普通、B、F、BF状态下的M、L、R |
| 跑车 | 12 | 普通、B、F、BF状态下的M、L、R |
| 合计 | 57 | 六个测试套件 |

两个车型文件分别使用一个 `TEST_P` 测试体，通过 `INSTANTIATE_TEST_SUITE_P` 各实例化12组数据。输出以指令作为名称后缀，例如 `/BFM`。参数化减少重复代码，但不减少实际场景数量。

现有测试未穷尽所有车型的TR行为、所有初始朝向、长序列或跨调用状态切换。最终位姿断言验证终点，逐格执行顺序还需结合动作编排代码检查。

## 常见问题

- **生成器不匹配**：不要让Visual Studio和MinGW共用构建目录。VS Code工作区配置使用 `build-vscode`，脚本使用 `build`。改变生成器或移动工程后，应备份旧生成目录，再重新配置。
- **新增测试没有出现**：确认文件保存，并运行完整的 `build_and_run.bat`；不要仅运行旧程序。通过 `--gtest_list_tests` 可以核对实际注册的用例。
- **CMake兼容错误**：主工程已更新最低版本声明，测试构建文件对旧版GoogleTest设置兼容策略，请使用当前工程配置和脚本。
- **缺少GoogleTest**：检查 `tests/googletest` 是否完整。该目录被Git忽略，重新取得工程时需要另外准备。
- **找不到工具**：检查CMake与MinGW安装情况，以及可执行文件所在目录是否加入PATH。

## 实验演进

- 实验1：建立工程与基础指令测试。
- 实验2：命令封装、接口继承与多态、F加速功能。
- 实验3：状态抽离、表驱动、坐标与方向抽象、Lambda与函数对象、B倒车功能。
- 实验4：单例工厂、原子操作编排、TR掉头、模块目录、公交车与跑车、数据驱动测试。

通过独立提交记录结构变化、测试新增与功能实现。验证时应核对构建成功及完整测试数量，避免将旧程序的通过结果误作新增功能的验证。
