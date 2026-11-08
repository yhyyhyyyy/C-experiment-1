#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"
#include "VehicleTestCase.hpp"

namespace adas
{
namespace
{
const VehicleTestCase sportsCarCases[] = {
    {"M", {0, 0, 'E'}, {2, 0, 'E'}},
    {"L", {0, 0, 'E'}, {0, 1, 'N'}},
    {"R", {0, 0, 'E'}, {0, -1, 'S'}},
    {"BM", {0, 0, 'E'}, {-2, 0, 'E'}},
    {"BL", {0, 0, 'E'}, {0, 1, 'S'}},
    {"BR", {0, 0, 'E'}, {0, -1, 'N'}},
    {"FM", {0, 0, 'E'}, {4, 0, 'E'}},
    {"FL", {0, 0, 'E'}, {1, 1, 'N'}},
    {"FR", {0, 0, 'E'}, {1, -1, 'S'}},
    {"BFM", {0, 0, 'E'}, {-4, 0, 'E'}},
    {"BFL", {0, 0, 'E'}, {-1, 1, 'S'}},
    {"BFR", {0, 0, 'E'}, {-1, -1, 'N'}},
};
}  // namespace

class ExecutorSportsCarTest : public ::testing::TestWithParam<VehicleTestCase>
{
};

TEST_P(ExecutorSportsCarTest, should_match_expected_pose)
{
    const auto& testCase = GetParam();

    // given
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor(testCase.initial, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    // when
    executor->Execute(testCase.commands);

    // then
    ASSERT_EQ(testCase.expected, executor->Query());
}

INSTANTIATE_TEST_SUITE_P(
    SportsCarScenarios, ExecutorSportsCarTest, ::testing::ValuesIn(sportsCarCases),
    [](const ::testing::TestParamInfo<VehicleTestCase>& info) {
        return std::string(info.param.commands);
    });
}  // namespace adas
