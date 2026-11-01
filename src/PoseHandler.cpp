#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& pose) noexcept
    : position(pose.x, pose.y), direction(pose.heading)
{
}

void PoseHandler::Move() noexcept
{
    const Point movement = direction.GetMove();

    if (reverse) {
        position += Point{-movement.GetX(), -movement.GetY()};
    } else {
        position += movement;
    }
}

void PoseHandler::TurnLeft() noexcept
{
    if (reverse) {
        direction.TurnRight();
    } else {
        direction.TurnLeft();
    }
}

void PoseHandler::TurnRight() noexcept
{
    if (reverse) {
        direction.TurnLeft();
    } else {
        direction.TurnRight();
    }
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}

Pose PoseHandler::Query() const noexcept
{
    return {position.GetX(), position.GetY(), direction.GetHeading()};
}
}  // namespace adas
