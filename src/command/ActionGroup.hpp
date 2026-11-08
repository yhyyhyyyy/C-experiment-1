#pragma once

#include "pose/PoseHandler.hpp"

#include <cstdint>
#include <list>

namespace adas
{
enum class ActionType : std::uint16_t
{
    FORWARD_1_STEP_ACTION = 0,
    BACKWARD_1_STEP_ACTION,
    TURNLEFT_ACTION,
    REVERSE_TURNLEFT_ACTION,
    TURNRIGHT_ACTION,
    REVERSE_TURNRIGHT_ACTION,
    BE_FAST_ACTION,
    BE_REVERSE_ACTION
};

class ActionGroup final
{
public:
    ActionGroup() = default;
    explicit ActionGroup(const std::list<ActionType>& actions) noexcept;

    void PushAction(ActionType actionType) noexcept;
    void DoOperate(PoseHandler& poseHandler) const noexcept;

private:
    std::list<ActionType> actions;
};
}  // namespace adas
