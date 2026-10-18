#include <gtest/gtest.h>

#include <memory>
#include <tuple>

#include "Executor.hpp"

namespace adas
{
bool operator==(const Pose& lhs, const Pose& rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
}

TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when：不执行指令

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor.get());

    // when：不指定初始状态，也不执行指令

    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose target{1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose target{-1, 0, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_y_plus_1_given_command_is_M_and_facing_is_N)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_y_minus_1_given_command_is_M_and_facing_is_S)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("M");

    const Pose target{0, -1, 'S'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_facing_N_given_command_is_L_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose target{2, 3, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_W_given_command_is_L_and_facing_is_N)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose target{2, 3, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_S_given_command_is_L_and_facing_is_W)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'W'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose target{2, 3, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_E_given_command_is_L_and_facing_is_S)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'S'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("L");

    const Pose target{2, 3, 'E'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_return_facing_S_given_command_is_R_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose target{2, 3, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_W_given_command_is_R_and_facing_is_S)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'S'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose target{2, 3, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_N_given_command_is_R_and_facing_is_W)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'W'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose target{2, 3, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_E_given_command_is_R_and_facing_is_N)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("R");

    const Pose target{2, 3, 'E'};
    ASSERT_EQ(target, executor->Query());
}
TEST(ExecutorTest, should_keep_pose_when_command_is_empty)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("");

    const Pose target{2, 3, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_move_three_steps_when_commands_are_MMM)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("MMM");

    const Pose target{0, 3, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_expected_pose_when_commands_are_MLMMRM)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("MLMMRM");

    const Pose target{-2, 2, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_keep_pose_after_four_left_turns)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("LLLL");

    const Pose target{2, 3, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_keep_pose_after_four_right_turns)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("RRRR");

    const Pose target{2, 3, 'E'};
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas