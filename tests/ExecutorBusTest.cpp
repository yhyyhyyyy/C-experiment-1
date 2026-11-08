#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
TEST(ExecutorBusTest, should_move_one_step_given_M)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("M");

    // then
    const Pose target{1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_then_turn_left_given_L)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("L");

    // then
    const Pose target{1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_then_turn_right_given_R)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("R");

    // then
    const Pose target{1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_backward_given_BM)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BM");

    // then
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_backward_then_turn_right_given_BL)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BL");

    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_backward_then_turn_left_given_BR)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BR");

    // then
    const Pose target{-1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_twice_given_FM)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("FM");

    // then
    const Pose target{2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_twice_then_turn_left_given_FL)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("FL");

    // then
    const Pose target{2, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_twice_then_turn_right_given_FR)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("FR");

    // then
    const Pose target{2, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_backward_twice_given_BFM)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFM");

    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_backward_twice_then_turn_right_given_BFL)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFL");

    // then
    const Pose target{-2, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorBusTest, should_move_backward_twice_then_turn_left_given_BFR)
{
    // given: the pose identifies the front of the bus.
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute("BFR");

    // then
    const Pose target{-2, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
