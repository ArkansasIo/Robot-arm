#include "forgearm/kinematics.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>
namespace forgearm {
namespace {
constexpr double kEpsilon=1e-9;
bool finite_pose(const Pose2D& p) noexcept {
 return std::isfinite(p.x)&&std::isfinite(p.y)&&std::isfinite(p.orientation);
}
double normalize_angle(double a) noexcept { return std::remainder(a,2.0*kPi); }
}
Kinematics::Kinematics(ArmConfig config):config_(std::move(config)) {
 for(double length:config_.link_lengths)
  if(!std::isfinite(length)||length<=0.0)
   throw std::invalid_argument("All link lengths must be finite and greater than zero.");
 for(const auto& limit:config_.limits)
  if(!std::isfinite(limit.minimum)||!std::isfinite(limit.maximum)||limit.minimum>=limit.maximum)
   throw std::invalid_argument("Each joint limit must be finite and minimum < maximum.");
}
const ArmConfig& Kinematics::config() const noexcept { return config_; }
Pose2D Kinematics::forward(const JointAngles& j) const noexcept {
 const double q1=j.q[0], q12=q1+j.q[1], q123=q12+j.q[2];
 const auto& l=config_.link_lengths;
 return {l[0]*std::cos(q1)+l[1]*std::cos(q12)+l[2]*std::cos(q123),
         l[0]*std::sin(q1)+l[1]*std::sin(q12)+l[2]*std::sin(q123),
         normalize_angle(q123)};
}
bool Kinematics::within_limits(const JointAngles& j) const noexcept {
 for(std::size_t i=0;i<j.q.size();++i)
  if(!std::isfinite(j.q[i])||j.q[i]<config_.limits[i].minimum-kEpsilon||
     j.q[i]>config_.limits[i].maximum+kEpsilon) return false;
 return true;
}
IkResult Kinematics::inverse(const Pose2D& t) const {
 if(!finite_pose(t)) return {false,{},"Target pose contains a non-finite value."};
 const auto& l=config_.link_lengths;
 const double wx=t.x-l[2]*std::cos(t.orientation), wy=t.y-l[2]*std::sin(t.orientation);
 double c=(wx*wx+wy*wy-l[0]*l[0]-l[1]*l[1])/(2.0*l[0]*l[1]);
 if(c < -1.0-kEpsilon || c > 1.0+kEpsilon)
  return {false,{},"Target is outside the geometric workspace."};
 c=std::clamp(c,-1.0,1.0);
 const double e=std::acos(c), candidates[2]={e,-e};
 for(double q2:candidates) {
  const double q1=std::atan2(wy,wx)-std::atan2(l[1]*std::sin(q2),l[0]+l[1]*std::cos(q2));
  const double q3=normalize_angle(t.orientation-q1-q2);
  JointAngles j{{normalize_angle(q1),normalize_angle(q2),q3}};
  if(within_limits(j)) {
   const Pose2D p=forward(j);
   if(std::hypot(p.x-t.x,p.y-t.y)<1e-6 &&
      std::abs(normalize_angle(p.orientation-t.orientation))<1e-6)
    return {true,j,"IK solution found."};
  }
 }
 return {false,{},"Target is geometrically reachable, but no solution satisfies joint limits."};
}
} // namespace forgearm
