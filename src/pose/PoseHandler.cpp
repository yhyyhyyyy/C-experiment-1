#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& pose) noexcept
    : position(pose.x, pose.y), direction(pose.heading)
{
}

void PoseHandler::Forward() noexcept
{
    position += direction.GetMove();
}

void PoseHandler::Backward() noexcept
{
    position -= direction.GetMove();
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

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}

bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}

Pose PoseHandler::Query() const noexcept
{
    return {position.GetX(), position.GetY(), direction.GetHeading()};
}
}  // namespace adas
