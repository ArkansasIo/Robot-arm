#include "forgearm/workspace.hpp"
#include <iostream>
int main(){using namespace forgearm;Workspace w(ArmConfig{});const auto r=w.radial_envelope();
 if(!(r.outer_radius>r.inner_radius))return 1;if(!w.inside_bounding_box({0,0}))return 2;
 if(w.inside_bounding_box({100,100}))return 3;Kinematics k;
 if(!w.pose_has_ik(k,k.forward(JointAngles{{0.1,0.2,-0.1}})))return 4;
 std::cout<<"Workspace tests passed.\n";return 0;}
