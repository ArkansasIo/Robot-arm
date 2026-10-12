#include "forgearm/hardware/mock_driver.hpp"
#include <cmath>
namespace forgearm::hardware {
std::string MockDriver::name()const{return "ForgeArm.MockDriver";}
DriverCapabilities MockDriver::capabilities()const noexcept{return {joints_.size(),true,false,false,true};}
DriverStatus MockDriver::status()const noexcept{std::scoped_lock lock(mutex_);return status_;}
DriverResult MockDriver::connect(const DriverConfig& c){
 std::scoped_lock lock(mutex_);
 if(c.arm_id.empty()||c.joint_names.empty())return {false,"arm_id and joint_names are required."};
 if(!std::isfinite(c.max_position_step_rad)||c.max_position_step_rad<=0.0)return {false,"max_position_step_rad must be positive."};
 config_=c;joints_.assign(c.joint_names.size(),JointTelemetry{});status_=DriverStatus::ready;return {true,"Mock driver connected; no physical hardware accessed."};
}
DriverResult MockDriver::enable(){std::scoped_lock lock(mutex_);if(status_!=DriverStatus::ready)return {false,"Driver must be connected before enable."};status_=DriverStatus::enabled;return {true,"Mock driver enabled."};}
DriverResult MockDriver::read(std::vector<JointTelemetry>& out){std::scoped_lock lock(mutex_);if(status_==DriverStatus::disconnected)return {false,"Driver is disconnected."};out=joints_;return {true,"Mock telemetry returned."};}
DriverResult MockDriver::command_position(const std::vector<double>& q){
 std::scoped_lock lock(mutex_);if(status_!=DriverStatus::enabled)return {false,"Driver is not enabled."};
 if(q.size()!=joints_.size())return {false,"Joint count mismatch."};
 for(double v:q)if(!std::isfinite(v))return {false,"Non-finite command rejected."};
 for(std::size_t i=0;i<q.size();++i){joints_[i].velocity=0.0;joints_[i].effort=0.0;joints_[i].position=q[i];joints_[i].valid=true;}
 return {true,"Mock command accepted; no physical hardware accessed."};
}
DriverResult MockDriver::stop()noexcept{std::scoped_lock lock(mutex_);if(status_==DriverStatus::enabled)status_=DriverStatus::ready;return {true,"Mock driver stopped."};}
void MockDriver::disconnect()noexcept{std::scoped_lock lock(mutex_);status_=DriverStatus::disconnected;joints_.clear();}
} // namespace forgearm::hardware
