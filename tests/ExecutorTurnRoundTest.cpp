#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
TEST(ExecutorTurnRoundTest, should_normal_tr_build_left_forward_left)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("TR");

    // then
    const Pose target{0, 1, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_fast_tr_build_forward_left_forward_left)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("FTR");

    // then
    const Pose target{1, 1, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_ignore_tr_in_reverse_state)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BTR");

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
