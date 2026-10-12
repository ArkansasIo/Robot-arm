#pragma once
#include "forgearm/kinematics.hpp"
#include "forgearm/math.hpp"
#include <array>
#include <vector>
namespace forgearm {
struct CircleObstacle { Vec2 center{}; double radius{}; };
struct Segment2D { Vec2 a{}; Vec2 b{}; };
[[nodiscard]] bool segments_intersect(Segment2D first,Segment2D second,double tolerance=1e-9) noexcept;
[[nodiscard]] double point_segment_distance(Vec2 point,Segment2D segment) noexcept;
[[nodiscard]] bool segment_intersects_circle(Segment2D segment,CircleObstacle circle,double clearance=0.0) noexcept;
[[nodiscard]] std::array<Vec2,4> link_points(const ArmConfig& config,const JointAngles& joints) noexcept;
[[nodiscard]] bool arm_intersects_obstacles(const ArmConfig& config,const JointAngles& joints,const std::vector<CircleObstacle>& obstacles,double link_radius=0.0) noexcept;
} // namespace forgearm
