#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
TEST(ExecutorReverseTest, should_move_backward_given_command_is_BM_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BM");

    // then
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_turn_right_given_command_is_BL_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BL");

    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_turn_left_given_command_is_BR_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BR");

    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_move_backward_twice_given_command_is_BFM_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFM");

    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_move_backward_then_turn_right_given_command_is_BFL_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFL");

    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_move_backward_then_turn_left_given_command_is_BFR_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFR");

    // then
    const Pose target{-1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_move_forward_given_command_is_BBM_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BBM");

    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
