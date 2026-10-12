#pragma once
#include "forgearm/collision.hpp"
#include "forgearm/trajectory.hpp"
#include <array>
#include <memory>
#include <string>
#include <vector>
namespace forgearm {
struct SimulatorState { JointAngles joints{}; Pose2D tool_pose{}; bool moving{false}; bool faulted{false}; std::string status{"Ready"}; };
class Simulator {
public:
 explicit Simulator(ArmConfig config={});
 [[nodiscard]] const SimulatorState& state()const noexcept;
 [[nodiscard]] const ArmConfig& config()const noexcept;
 [[nodiscard]] bool set_joints(const JointAngles& joints);
 [[nodiscard]] bool move_to(const JointAngles& target,MotionLimits limits);
 [[nodiscard]] bool step(double dt);
 void stop()noexcept;
 void reset()noexcept;
 void set_obstacles(std::vector<CircleObstacle> obstacles,double link_radius=0.0);
private:
 ArmConfig config_; Kinematics kinematics_; SimulatorState state_{};
 std::array<std::unique_ptr<TrapezoidalTrajectory>,3> trajectories_{};
 double elapsed_{0.0},duration_{0.0}; std::vector<CircleObstacle> obstacles_{}; double link_radius_{0.0};
};
} // namespace forgearm
