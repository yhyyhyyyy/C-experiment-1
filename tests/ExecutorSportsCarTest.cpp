#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
TEST(ExecutorSportsCarTest, should_move_two_steps_given_M)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("M");

    // then
    const Pose target{2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_turn_left_then_move_given_L)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("L");

    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_turn_right_then_move_given_R)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("R");

    // then
    const Pose target{0, -1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_move_backward_two_steps_given_BM)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BM");

    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_turn_right_then_move_backward_given_BL)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BL");

    // then
    const Pose target{0, 1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_turn_left_then_move_backward_given_BR)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BR");

    // then
    const Pose target{0, -1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_move_four_steps_given_FM)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("FM");

    // then
    const Pose target{4, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_move_then_turn_left_then_move_given_FL)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("FL");

    // then
    const Pose target{1, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_move_then_turn_right_then_move_given_FR)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("FR");

    // then
    const Pose target{1, -1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_move_backward_four_steps_given_BFM)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFM");

    // then
    const Pose target{-4, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_move_backward_then_turn_right_then_move_backward_given_BFL)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFL");

    // then
    const Pose target{-1, 1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorSportsCarTest, should_move_backward_then_turn_left_then_move_backward_given_BFR)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFR");

    // then
    const Pose target{-1, -1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
