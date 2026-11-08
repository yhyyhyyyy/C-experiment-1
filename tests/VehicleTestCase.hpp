#pragma once

#include "Executor.hpp"

namespace adas
{
struct VehicleTestCase
{
    const char* commands;
    Pose initial;
    Pose expected;
};
}  // namespace adas
