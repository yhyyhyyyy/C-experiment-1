#pragma once

#include <string>

namespace adas
{
struct Pose {
    int x;
    int y;
    char heading;
};

class Executor
{
public:
    // 返回的对象由调用者负责释放。
    static Executor* NewExecutor(const Pose& pose) noexcept;

    Executor() = default;
    virtual ~Executor() = default;

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    virtual void Execute(const std::string& commands) noexcept = 0;
    virtual Pose Query() const noexcept = 0;
};
}  // namespace adas