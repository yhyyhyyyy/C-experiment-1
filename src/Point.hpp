#pragma once

namespace adas
{
class Point final
{
public:
    Point(int x, int y) noexcept : x(x), y(y)
    {
    }

    Point(const Point&) = default;
    Point& operator=(const Point&) = default;

    Point& operator+=(const Point& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    int GetX() const noexcept
    {
        return x;
    }

    int GetY() const noexcept
    {
        return y;
    }

private:
    int x;
    int y;
};
}  // namespace adas