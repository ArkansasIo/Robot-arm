#pragma once
#include <string>
#include <vector>
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp_lifecycle/state.hpp"
namespace forgearm_ros2_hardware {
class ForgeArmSystem final : public hardware_interface::SystemInterface {
public:
 RCLCPP_SHARED_PTR_DEFINITIONS(ForgeArmSystem)
 hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo& info) override;
 std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
 std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;
 hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;
 hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State& previous_state) override;
 hardware_interface::return_type read(const rclcpp::Time& time,const rclcpp::Duration& period) override;
 hardware_interface::return_type write(const rclcpp::Time& time,const rclcpp::Duration& period) override;
private:
 bool mock_mode_{false};
 std::vector<double> position_state_,position_command_;
};
} // namespace forgearm_ros2_hardware
