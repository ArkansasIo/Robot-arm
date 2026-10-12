#include "forgearm/trajectory.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
int main(){using namespace forgearm;try{
 TrapezoidalTrajectory t(0.0,10.0,{2.0,1.0});
 if(std::abs(t.sample(0).position)>1e-9)throw std::runtime_error("start mismatch");
 if(std::abs(t.sample(t.duration()).position-10.0)>1e-9)throw std::runtime_error("end mismatch");
 for(int i=0;i<=1000;++i){auto s=t.sample(t.duration()*static_cast<double>(i)/1000.0);if(std::abs(s.velocity)>2.0+1e-8)throw std::runtime_error("velocity limit exceeded");}
 TrapezoidalTrajectory reverse(3.0,-2.0,{1.0,2.0});if(std::abs(reverse.sample(reverse.duration()).position+2.0)>1e-9)throw std::runtime_error("reverse endpoint mismatch");
 std::cout<<"Trajectory tests passed.\n";return 0;
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
