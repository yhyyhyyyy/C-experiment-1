#include "ExecutorImpl.hpp"
#include "Command.hpp"

#include <functional>
#include <new>
#include <unordered_map>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept
    : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap{
        {'M', MoveCommand{}},
        {'L', TurnLeftCommand{}},
        {'R', TurnRightCommand{}},
        {'F', FastCommand{}},
        {'B', ReverseCommand{}}
    };

    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);

        if (it != cmderMap.end()) {
            it->second(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
