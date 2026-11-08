#pragma once

#include "ActionGroup.hpp"

namespace adas
{
class MoveCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto moveAction = poseHandler.IsReverse()
            ? ActionType::BACKWARD_1_STEP_ACTION
            : ActionType::FORWARD_1_STEP_ACTION;
        const int baseSteps = poseHandler.GetVehicleType() == VehicleType::SportsCar ? 2 : 1;
        const int steps = poseHandler.IsFast() ? baseSteps * 2 : baseSteps;

        for (int step = 0; step < steps; ++step) {
            actionGroup.PushAction(moveAction);
        }

        return actionGroup;
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto moveAction = poseHandler.IsReverse()
            ? ActionType::BACKWARD_1_STEP_ACTION
            : ActionType::FORWARD_1_STEP_ACTION;

        if (poseHandler.IsFast()) {
            actionGroup.PushAction(moveAction);
        }

        if (poseHandler.GetVehicleType() == VehicleType::Bus) {
            actionGroup.PushAction(moveAction);
        }

        actionGroup.PushAction(poseHandler.IsReverse()
            ? ActionType::REVERSE_TURNLEFT_ACTION
            : ActionType::TURNLEFT_ACTION);

        if (poseHandler.GetVehicleType() == VehicleType::SportsCar) {
            actionGroup.PushAction(moveAction);
        }

        return actionGroup;
    }
};

class TurnRightCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto moveAction = poseHandler.IsReverse()
            ? ActionType::BACKWARD_1_STEP_ACTION
            : ActionType::FORWARD_1_STEP_ACTION;

        if (poseHandler.IsFast()) {
            actionGroup.PushAction(moveAction);
        }

        if (poseHandler.GetVehicleType() == VehicleType::Bus) {
            actionGroup.PushAction(moveAction);
        }

        actionGroup.PushAction(poseHandler.IsReverse()
            ? ActionType::REVERSE_TURNRIGHT_ACTION
            : ActionType::TURNRIGHT_ACTION);

        if (poseHandler.GetVehicleType() == VehicleType::SportsCar) {
            actionGroup.PushAction(moveAction);
        }

        return actionGroup;
    }
};

class FastCommand final
{
public:
    ActionGroup operator()(PoseHandler&) const noexcept
    {
        return ActionGroup({ActionType::BE_FAST_ACTION});
    }
};

class ReverseCommand final
{
public:
    ActionGroup operator()(PoseHandler&) const noexcept
    {
        return ActionGroup({ActionType::BE_REVERSE_ACTION});
    }
};

class TurnRoundCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsReverse()) {
            return ActionGroup{};
        }

        ActionGroup actionGroup;

        if (poseHandler.IsFast()) {
            actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
        }

        actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
        actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
        actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
        return actionGroup;
    }
};
}  // namespace adas
