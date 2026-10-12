#pragma once
#include "forgearm/kinematics.hpp"
#include "forgearm/math.hpp"
namespace forgearm {
struct WorkspaceEnvelope { double inner_radius{}; double outer_radius{}; };
class Workspace {
public:
 explicit Workspace(const ArmConfig& config);
 [[nodiscard]] WorkspaceEnvelope radial_envelope() const noexcept;
 [[nodiscard]] bool inside_radial_envelope(Vec2 point,double tolerance=1e-9) const noexcept;
 [[nodiscard]] bool inside_bounding_box(Vec2 point,double tolerance=1e-9) const noexcept;
 [[nodiscard]] bool pose_has_ik(const Kinematics& kinematics,const Pose2D& pose) const;
private: double minimum_radius_{},maximum_radius_{};
};
} // namespace forgearm
