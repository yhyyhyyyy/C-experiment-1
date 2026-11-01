#pragma once

#include <string_view>

#include "Point.hpp"

namespace adas
{
class Direction final
{
public:
    explicit Direction(char heading) noexcept : heading(heading)
    {
    }

    void TurnLeft() noexcept
    {
        const std::string_view headings{"NESW"};
        const auto index = headings.find(heading);

        if (index != std::string_view::npos) {
            heading = headings[(index + 3) % 4];
        }
    }

    void TurnRight() noexcept
    {
        const std::string_view headings{"NESW"};
        const auto index = headings.find(heading);

        if (index != std::string_view::npos) {
            heading = headings[(index + 1) % 4];
        }
    }

    Point GetMove() const noexcept
    {
        const std::string_view headings{"NESW"};
        const Point movements[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        const auto index = headings.find(heading);

        if (index != std::string_view::npos) {
            return movements[index];
        }

        return {0, 0};
    }

    char GetHeading() const noexcept
    {
        return heading;
    }

private:
    char heading;
};
}  // namespace adas