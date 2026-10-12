#include "forgearm/hardware/safety_gate.hpp"
#include <cmath>
#include <stdexcept>
namespace forgearm::hardware {
SafetyGate::SafetyGate(SafetyLimits limits):limits_(std::move(limits)){
 if(limits_.joint_limits.empty())throw std::invalid_argument("SafetyGate requires at least one joint limit.");
 if(!std::isfinite(limits_.max_command_step_rad)||limits_.max_command_step_rad<=0.0||
    !std::isfinite(limits_.max_velocity_rad_s)||limits_.max_velocity_rad_s<=0.0)
  throw std::invalid_argument("Safety limits must be positive and finite.");
 for(const auto& l:limits_.joint_limits)if(!std::isfinite(l.minimum)||!std::isfinite(l.maximum)||l.minimum>=l.maximum)
  throw std::invalid_argument("Invalid joint limit.");
}
GateResult SafetyGate::validate_command(const std::vector<double>& current,const std::vector<double>& target)const{
 if(current.size()!=limits_.joint_limits.size()||target.size()!=limits_.joint_limits.size())return {false,"Joint count mismatch."};
 for(std::size_t i=0;i<target.size();++i){
  if(!std::isfinite(current[i])||!std::isfinite(target[i]))return {false,"Non-finite joint value."};
  if(target[i]<limits_.joint_limits[i].minimum||target[i]>limits_.joint_limits[i].maximum)return {false,"Joint target exceeds configured software limits."};
  if(std::abs(target[i]-current[i])>limits_.max_command_step_rad)return {false,"Command step exceeds configured limit."};
 }
 return {true,"Command passed software checks."};
}
const SafetyLimits& SafetyGate::limits()const noexcept{return limits_;}
} // namespace forgearm::hardware
