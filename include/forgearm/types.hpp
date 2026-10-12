#pragma once
#include <array>
#include <cmath>
#include <string>
namespace forgearm {
inline constexpr double kPi = 3.14159265358979323846;
[[nodiscard]] inline constexpr double deg_to_rad(double v) noexcept { return v*kPi/180.0; }
[[nodiscard]] inline constexpr double rad_to_deg(double v) noexcept { return v*180.0/kPi; }
struct Pose2D { double x{}; double y{}; double orientation{}; };
struct JointAngles { std::array<double,3> q{}; };
struct JointLimit { double minimum{}; double maximum{}; };
struct ArmConfig {
 std::array<double,3> link_lengths{1.0,0.8,0.3};
 std::array<JointLimit,3> limits{{
  {deg_to_rad(-170.0),deg_to_rad(170.0)},
  {deg_to_rad(-150.0),deg_to_rad(150.0)},
  {deg_to_rad(-170.0),deg_to_rad(170.0)}
 }};
};
struct IkResult { bool success{false}; JointAngles joints{}; std::string message; };
} // namespace forgearm
