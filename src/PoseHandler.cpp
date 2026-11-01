#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& pose) noexcept : position(pose.x, pose.y), direction(pose.heading)
{
}

void PoseHandler::Move() noexcept
{
    position += direction.GetMove();
}

void PoseHandler::TurnLeft() noexcept
{
    direction.TurnLeft();
}

void PoseHandler::TurnRight() noexcept
{
    direction.TurnRight();
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

Pose PoseHandler::Query() const noexcept
{
    return {position.GetX(), position.GetY(), direction.GetHeading()};
}
}  // namespace adas