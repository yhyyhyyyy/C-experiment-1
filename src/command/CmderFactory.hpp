#pragma once

#include "Command.hpp"

#include <functional>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>

namespace adas
{
using Cmder = std::function<ActionGroup(PoseHandler&)>;
using CmderList = std::list<Cmder>;

class CmderFactory final
{
public:
    CmderFactory() = default;
    ~CmderFactory() = default;

    CmderFactory(const CmderFactory&) = delete;
    CmderFactory& operator=(const CmderFactory&) = delete;

    CmderList GetCmders(const std::string& commands) const noexcept;

private:
    std::string ParseCommandString(std::string_view commands) const noexcept;
    void ReplaceAll(std::string& inout, std::string_view what,
                    std::string_view with) const noexcept;

private:
    const std::unordered_map<char, Cmder> cmderMap{
        {'M', MoveCommand{}},
        {'L', TurnLeftCommand{}},
        {'R', TurnRightCommand{}},
        {'F', FastCommand{}},
        {'B', ReverseCommand{}},
        {'Z', TurnRoundCommand{}}
    };
};
}  // namespace adas
