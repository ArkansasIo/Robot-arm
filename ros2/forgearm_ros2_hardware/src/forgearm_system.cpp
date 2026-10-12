#include "forgearm_ros2_hardware/forgearm_system.hpp"
#include <cmath>
#include <limits>
#include "pluginlib/class_list_macros.hpp"
namespace forgearm_ros2_hardware {
hardware_interface::CallbackReturn ForgeArmSystem::on_init(const hardware_interface::HardwareInfo& info) {
 if(hardware_interface::SystemInterface::on_init(info)!=hardware_interface::CallbackReturn::SUCCESS)
  return hardware_interface::CallbackReturn::ERROR;
 const auto it=info.hardware_parameters.find("mock_mode");
 mock_mode_=(it!=info.hardware_parameters.end() && it->second=="true");
 if(info_.joints.empty())return hardware_interface::CallbackReturn::ERROR;
 position_state_.assign(info_.joints.size(),0.0);
 position_command_.assign(info_.joints.size(),0.0);
 for(const auto& joint:info_.joints) {
  bool has_position_command=false,has_position_state=false;
  for(const auto& ci:joint.command_interfaces)if(ci.name==hardware_interface::HW_IF_POSITION)has_position_command=true;
  for(const auto& si:joint.state_interfaces)if(si.name==hardware_interface::HW_IF_POSITION)has_position_state=true;
  if(!has_position_command||!has_position_state)return hardware_interface::CallbackReturn::ERROR;
 }
 return hardware_interface::CallbackReturn::SUCCESS;
}
std::vector<hardware_interface::StateInterface> ForgeArmSystem::export_state_interfaces() {
 std::vector<hardware_interface::StateInterface> out;
 for(std::size_t i=0;i<info_.joints.size();++i)
  out.emplace_back(info_.joints[i].name,hardware_interface::HW_IF_POSITION,&position_state_[i]);
 return out;
}
std::vector<hardware_interface::CommandInterface> ForgeArmSystem::export_command_interfaces() {
 std::vector<hardware_interface::CommandInterface> out;
 for(std::size_t i=0;i<info_.joints.size();++i)
  out.emplace_back(info_.joints[i].name,hardware_interface::HW_IF_POSITION,&position_command_[i]);
 return out;
}
hardware_interface::CallbackReturn ForgeArmSystem::on_activate(const rclcpp_lifecycle::State&) {
 // Fail closed: this scaffold cannot operate physical hardware.
 if(!mock_mode_)return hardware_interface::CallbackReturn::ERROR;
 position_command_=position_state_;
 return hardware_interface::CallbackReturn::SUCCESS;
}
hardware_interface::CallbackReturn ForgeArmSystem::on_deactivate(const rclcpp_lifecycle::State&) {
 position_command_=position_state_;
 return hardware_interface::CallbackReturn::SUCCESS;
}
hardware_interface::return_type ForgeArmSystem::read(const rclcpp::Time&,const rclcpp::Duration&) {
 if(!mock_mode_)return hardware_interface::return_type::ERROR;
 return hardware_interface::return_type::OK;
}
hardware_interface::return_type ForgeArmSystem::write(const rclcpp::Time&,const rclcpp::Duration&) {
 if(!mock_mode_)return hardware_interface::return_type::ERROR;
 for(double v:position_command_)if(!std::isfinite(v))return hardware_interface::return_type::ERROR;
 // Mock only: mimic command values as state. No hardware communication occurs.
 position_state_=position_command_;
 return hardware_interface::return_type::OK;
}
} // namespace forgearm_ros2_hardware
PLUGINLIB_EXPORT_CLASS(forgearm_ros2_hardware::ForgeArmSystem,hardware_interface::SystemInterface)
