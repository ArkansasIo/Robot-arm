#include "forgearm/kinematics.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
namespace { void require(bool ok,const char* m){if(!ok) throw std::runtime_error(m);} }
int main() {
 using namespace forgearm;
 try {
  const Kinematics arm;
  const JointAngles original{{deg_to_rad(25.0),deg_to_rad(45.0),deg_to_rad(-20.0)}};
  const Pose2D pose=arm.forward(original);
  const IkResult solved=arm.inverse(pose);
  require(solved.success,"IK should recover a valid pose");
  const Pose2D rebuilt=arm.forward(solved.joints);
  require(std::hypot(rebuilt.x-pose.x,rebuilt.y-pose.y)<1e-6,"FK/IK position round-trip failed");
  require(std::abs(std::remainder(rebuilt.orientation-pose.orientation,2.0*kPi))<1e-6,"FK/IK orientation round-trip failed");
  require(arm.within_limits(original),"Valid joint configuration rejected");
  require(!arm.inverse({100.0,100.0,0.0}).success,"Unreachable pose incorrectly accepted");
  require(!arm.inverse({std::numeric_limits<double>::quiet_NaN(),0.0,0.0}).success,"Non-finite pose incorrectly accepted");
  bool rejected=false;
  try { ArmConfig bad; bad.link_lengths[0]=0.0; (void)Kinematics{bad}; }
  catch(const std::invalid_argument&) { rejected=true; }
  require(rejected,"Invalid link length was not rejected");
  std::cout<<"All ForgeArm tests passed.\n"; return 0;
 } catch(const std::exception& e) { std::cerr<<"TEST FAILURE: "<<e.what()<<'\n'; return 1; }
}
