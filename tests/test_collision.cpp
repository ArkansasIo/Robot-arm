#include "forgearm/collision.hpp"
#include <iostream>
int main(){using namespace forgearm;
 if(!segments_intersect({{0,0},{2,2}},{{0,2},{2,0}}))return 1;
 if(segments_intersect({{0,0},{1,0}},{{2,0},{3,0}}))return 2;
 if(!segment_intersects_circle({{0,0},{3,0},},{{1,0},0.2}))return 3;
 if(segment_intersects_circle({{0,0},{1,0}},{{3,0},0.2}))return 4;
 if(!arm_intersects_obstacles(ArmConfig{},JointAngles{{0,0,0}},{{{1.0,0.0},0.2}}))return 5;
 std::cout<<"Collision tests passed.\n";return 0;}
