#pragma once
#include <cmath>
namespace forgearm {
struct Vec2 {
 double x{}, y{};
 [[nodiscard]] constexpr Vec2 operator+(const Vec2& r) const noexcept { return {x+r.x,y+r.y}; }
 [[nodiscard]] constexpr Vec2 operator-(const Vec2& r) const noexcept { return {x-r.x,y-r.y}; }
 [[nodiscard]] constexpr Vec2 operator*(double s) const noexcept { return {x*s,y*s}; }
 [[nodiscard]] constexpr double dot(const Vec2& r) const noexcept { return x*r.x+y*r.y; }
 [[nodiscard]] double length() const noexcept { return std::hypot(x,y); }
};
[[nodiscard]] inline double distance(const Vec2& a,const Vec2& b) noexcept { return (a-b).length(); }
} // namespace forgearm
