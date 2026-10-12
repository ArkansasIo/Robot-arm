#include "forgearm/kinematics.hpp"
#include <exception>
#include <iomanip>
#include <iostream>
int main() {
 using namespace forgearm;
 try {
  const Kinematics arm;
  const JointAngles home{{deg_to_rad(25.0),deg_to_rad(45.0),deg_to_rad(-20.0)}};
  const Pose2D pose=arm.forward(home);
  std::cout<<"ForgeArm C++23 — planar 3-DOF simulator\n---------------------------------------\n"
           <<std::fixed<<std::setprecision(3)
           <<"Joint angles (deg): shoulder="<<rad_to_deg(home.q[0])
           <<", elbow="<<rad_to_deg(home.q[1])<<", wrist="<<rad_to_deg(home.q[2])<<'\n'
           <<"FK tool pose: x="<<pose.x<<", y="<<pose.y
           <<", orientation="<<rad_to_deg(pose.orientation)<<" deg\n\n";
  const IkResult r=arm.inverse(pose);
  std::cout<<"Inverse kinematics: "<<r.message<<'\n';
  if(r.success) { std::cout<<"One valid solution (deg): "; for(double a:r.joints.q) std::cout<<rad_to_deg(a)<<' '; std::cout<<'\n'; }
  std::cout<<"\nSimulation only. No motors or hardware are controlled.\n";
  return r.success?0:1;
 } catch(const std::exception& e) { std::cerr<<"Fatal configuration error: "<<e.what()<<'\n'; return 2; }
}
