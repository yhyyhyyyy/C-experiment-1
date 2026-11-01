#pragma once

#include "Direction.hpp"
#include "Executor.hpp"
#include "Point.hpp"

namespace adas
{
class PoseHandler final
{
public:
    explicit PoseHandler(const Pose& pose) noexcept;

    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

    void Fast() noexcept;
    bool IsFast() const noexcept;

    void Reverse() noexcept;

    Pose Query() const noexcept;

private:
    Point position;
    Direction direction;
    bool fast{false};
    bool reverse{false};
};
}  // namespace adas
