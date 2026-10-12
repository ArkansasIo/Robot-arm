#include "forgearm/simulator.hpp"
#include <algorithm>
#include <cmath>
#include <exception>
#include <utility>
namespace forgearm {
Simulator::Simulator(ArmConfig c):config_(std::move(c)),kinematics_(config_){state_.tool_pose=kinematics_.forward(state_.joints);}
const SimulatorState& Simulator::state()const noexcept{return state_;}
const ArmConfig& Simulator::config()const noexcept{return config_;}
bool Simulator::set_joints(const JointAngles& q){
 if(state_.faulted||!kinematics_.within_limits(q)){state_.status="Rejected invalid joint state";return false;}
 if(arm_intersects_obstacles(config_,q,obstacles_,link_radius_)){state_.status="Rejected state: collision detected";return false;}
 state_.joints=q;state_.tool_pose=kinematics_.forward(q);state_.moving=false;state_.status="Joint state updated";for(auto& t:trajectories_)t.reset();return true;
}
bool Simulator::move_to(const JointAngles& target,MotionLimits limits){
 if(state_.faulted){state_.status="Cannot move while faulted";return false;}
 if(!kinematics_.within_limits(target)){state_.status="Target violates joint limits";return false;}
 if(arm_intersects_obstacles(config_,target,obstacles_,link_radius_)){state_.status="Target is in collision";return false;}
 try{duration_=0.0;for(std::size_t i=0;i<3;++i){trajectories_[i]=std::make_unique<TrapezoidalTrajectory>(state_.joints.q[i],target.q[i],limits);duration_=std::max(duration_,trajectories_[i]->duration());}}
 catch(const std::exception& e){state_.status=std::string("Trajectory rejected: ")+e.what();return false;}
 elapsed_=0.0;state_.moving=duration_>0.0;state_.status=state_.moving?"Trajectory running":"Target already reached";
 if(!state_.moving){state_.joints=target;state_.tool_pose=kinematics_.forward(target);}return true;
}
bool Simulator::step(double dt){
 if(!std::isfinite(dt)||dt<0.0){state_.status="Invalid simulation timestep";return false;}
 if(state_.faulted)return false;if(!state_.moving)return true;
 elapsed_=std::min(elapsed_+dt,duration_);JointAngles next{};
 for(std::size_t i=0;i<3;++i)next.q[i]=trajectories_[i]->sample(elapsed_).position;
 if(arm_intersects_obstacles(config_,next,obstacles_,link_radius_)){state_.faulted=true;state_.moving=false;state_.status="Fault: collision encountered during trajectory";return false;}
 state_.joints=next;state_.tool_pose=kinematics_.forward(next);
 if(elapsed_>=duration_){state_.moving=false;state_.status="Trajectory complete";}return true;
}
void Simulator::stop()noexcept{state_.moving=false;for(auto& t:trajectories_)t.reset();state_.status="Stopped (simulation)";}
void Simulator::reset()noexcept{state_.joints={};state_.tool_pose=kinematics_.forward(state_.joints);state_.moving=false;state_.faulted=false;elapsed_=duration_=0.0;for(auto& t:trajectories_)t.reset();state_.status="Reset";}
void Simulator::set_obstacles(std::vector<CircleObstacle> o,double r){
 if(!std::isfinite(r)||r<0.0){state_.status="Invalid link radius";return;}obstacles_=std::move(o);link_radius_=r;
 if(arm_intersects_obstacles(config_,state_.joints,obstacles_,link_radius_)){state_.faulted=true;state_.moving=false;state_.status="Fault: current state intersects obstacle";}
}
} // namespace forgearm
