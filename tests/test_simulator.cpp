#include "forgearm/simulator.hpp"
#include <cmath>
#include <iostream>
int main() {
 using namespace forgearm;
 Simulator sim;
 const JointAngles target{{deg_to_rad(20.0),deg_to_rad(30.0),deg_to_rad(-10.0)}};
 if(!sim.move_to(target,{1.0,2.0})) return 1;
 if(!sim.state().moving && sim.state().status!="Target already reached") return 2;
 for(int i=0;i<2000 && sim.state().moving;++i) if(!sim.step(0.01)) return 3;
 if(sim.state().moving) return 4;
 for(std::size_t i=0;i<3;++i) if(std::abs(sim.state().joints.q[i]-target.q[i])>1e-6) return 5;
 sim.reset();
 if(sim.state().faulted || sim.state().moving) return 6;
 if(!sim.set_joints(target)) return 7;
 sim.set_obstacles({{{0.0,0.0},0.5}},0.0);
 if(!sim.state().faulted) return 8;
 std::cout<<"Simulator tests passed.\n";
 return 0;
}
