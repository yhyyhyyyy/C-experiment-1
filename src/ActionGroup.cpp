#include "ActionGroup.hpp"

#include <array>
#include <cstddef>
#include <functional>

namespace adas
{
namespace
{
class ForwardAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Forward();
    }
};

class BackwardAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Backward();
    }
};

class TurnLeftAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnLeft();
    }
};

class ReverseTurnLeftAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnRight();
    }
};

class TurnRightAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnRight();
    }
};

class ReverseTurnRightAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnLeft();
    }
};

class BeFastAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Fast();
    }
};

class BeReverseAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Reverse();
    }
};
}  // namespace

ActionGroup::ActionGroup(const std::list<ActionType>& actions) noexcept
    : actions(actions)
{
}

void ActionGroup::PushAction(ActionType actionType) noexcept
{
    actions.push_back(actionType);
}

void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept
{
    using Action = std::function<void(PoseHandler&)>;

    // Keep this order aligned with the ActionType enumerators.
    static const std::array<Action, 8> actionTable{
        ForwardAction{},
        BackwardAction{},
        TurnLeftAction{},
        ReverseTurnLeftAction{},
        TurnRightAction{},
        ReverseTurnRightAction{},
        BeFastAction{},
        BeReverseAction{}
    };

    for (const auto actionType : actions) {
        actionTable[static_cast<std::size_t>(actionType)](poseHandler);
    }
}
}  // namespace adas
