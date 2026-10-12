#pragma once
#include "forgearm/types.hpp"
#include <string>
#include <vector>
namespace forgearm::hardware {
struct SafetyLimits {
 std::vector<JointLimit> joint_limits;
 double max_command_step_rad{0.05};
 double max_velocity_rad_s{1.0};
 bool require_valid_feedback{true};
};
struct GateResult { bool allowed{false}; std::string reason; };
class SafetyGate {
public:
 explicit SafetyGate(SafetyLimits limits);
 [[nodiscard]] GateResult validate_command(const std::vector<double>& current,const std::vector<double>& target) const;
 [[nodiscard]] const SafetyLimits& limits() const noexcept;
private: SafetyLimits limits_;
};
} // namespace forgearm::hardware
