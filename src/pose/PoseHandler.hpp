#pragma once

#include "Direction.hpp"
#include "Executor.hpp"
#include "Point.hpp"

namespace adas
{
class PoseHandler final
{
public:
    explicit PoseHandler(const Pose& pose,
                         VehicleType vehicleType = VehicleType::Normal) noexcept;

    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

    void Forward() noexcept;
    void Backward() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

    void Fast() noexcept;
    bool IsFast() const noexcept;

    void Reverse() noexcept;
    bool IsReverse() const noexcept;

    VehicleType GetVehicleType() const noexcept;

    Pose Query() const noexcept;

private:
    Point position;
    Direction direction;
    const VehicleType vehicleType;
    bool fast{false};
    bool reverse{false};
};
}  // namespace adas
