#include "forgearm/hardware/arm_group.hpp"
#include <algorithm>
#include <utility>
namespace forgearm::hardware {
ArmGroup::ArmGroup(std::size_t max):maximum_arms_(max){if(maximum_arms_==0)maximum_arms_=1;}
DriverResult ArmGroup::add_arm(std::string id,std::shared_ptr<IHardwareDriver> driver,SafetyGate* gate){
 if(id.empty()||!driver||!gate)return {false,"Arm id, driver, and safety gate are required."};
 if(arms_.size()>=maximum_arms_)return {false,"Arm group capacity reached."};
 if(std::any_of(arms_.begin(),arms_.end(),[&](const auto& a){return a.id==id;}))return {false,"Duplicate arm id."};
 arms_.push_back({std::move(id),std::move(driver),gate,{}});return {true,"Arm registered."};
}
std::size_t ArmGroup::size()const noexcept{return arms_.size();}
std::size_t ArmGroup::capacity()const noexcept{return maximum_arms_;}
std::vector<std::string> ArmGroup::arm_ids()const{std::vector<std::string> ids;for(const auto& a:arms_)ids.push_back(a.id);return ids;}
DriverResult ArmGroup::connect_all(const std::vector<DriverConfig>& configs){
 if(configs.size()!=arms_.size())return {false,"Provide exactly one driver config per registered arm."};
 for(auto& a:arms_){auto it=std::find_if(configs.begin(),configs.end(),[&](const auto& c){return c.arm_id==a.id;});if(it==configs.end())return {false,"Missing config for arm "+a.id};auto r=a.driver->connect(*it);if(!r.ok){(void)disconnect_all();return {false,"Connect failed for "+a.id+": "+r.message};}}
 return {true,"All registered drivers connected."};
}
DriverResult ArmGroup::enable_all(){for(auto& a:arms_){auto r=a.driver->enable();if(!r.ok){(void)stop_all();return {false,"Enable failed for "+a.id+": "+r.message};}}return {true,"All registered drivers enabled."};}
DriverResult ArmGroup::command(const std::string& id,const std::vector<double>& target){
 auto it=std::find_if(arms_.begin(),arms_.end(),[&](const auto& a){return a.id==id;});if(it==arms_.end())return {false,"Unknown arm id."};
 std::vector<JointTelemetry> telemetry;auto rr=it->driver->read(telemetry);if(!rr.ok)return rr;
 std::vector<double> current;current.reserve(telemetry.size());for(const auto& j:telemetry){if(!j.valid)return {false,"Feedback invalid; command rejected."};current.push_back(j.position);}
 const auto checked=it->gate->validate_command(current,target);if(!checked.allowed)return {false,checked.reason};
 auto result=it->driver->command_position(target);if(result.ok)it->last_command=target;return result;
}
DriverResult ArmGroup::stop_all()noexcept{bool ok=true;std::string msg;for(auto& a:arms_){auto r=a.driver->stop();if(!r.ok){ok=false;msg+=a.id+": "+r.message+"; ";}}return {ok,ok?"All drivers stopped.":msg};}
DriverResult ArmGroup::disconnect_all()noexcept{(void)stop_all();for(auto& a:arms_)a.driver->disconnect();return {true,"All drivers disconnected."};}
} // namespace forgearm::hardware
