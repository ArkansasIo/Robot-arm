#pragma once
#include "forgearm/types.hpp"
namespace forgearm {
class Kinematics {
public:
 explicit Kinematics(ArmConfig config = {});
 [[nodiscard]] const ArmConfig& config() const noexcept;
 [[nodiscard]] Pose2D forward(const JointAngles& joints) const noexcept;
 [[nodiscard]] IkResult inverse(const Pose2D& target) const;
 [[nodiscard]] bool within_limits(const JointAngles& joints) const noexcept;
private:
 ArmConfig config_;
};
} // namespace forgearm
