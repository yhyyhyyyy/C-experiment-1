#include "CmderFactory.hpp"

namespace adas
{
CmderList CmderFactory::GetCmders(const std::string& commands) const noexcept
{
    CmderList cmders;

    for (const auto cmd : ParseCommandString(commands)) {
        const auto it = cmderMap.find(cmd);

        if (it != cmderMap.end()) {
            cmders.push_back(it->second);
        }
    }

    return cmders;
}

std::string CmderFactory::ParseCommandString(std::string_view commands) const noexcept
{
    std::string result(commands);
    ReplaceAll(result, "TR", "Z");
    return result;
}

void CmderFactory::ReplaceAll(std::string& inout, std::string_view what, std::string_view with) const noexcept
{
    if (what.empty()) {
        return;
    }

    std::string::size_type pos = 0;

    while ((pos = inout.find(what.data(), pos, what.size())) != std::string::npos) {
        inout.replace(pos, what.size(), with.data(), with.size());
        pos += with.size();
    }
}
}  // namespace adas
