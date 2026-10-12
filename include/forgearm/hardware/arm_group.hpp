#pragma once
#include "forgearm/hardware/driver.hpp"
#include "forgearm/hardware/safety_gate.hpp"
#include <memory>
#include <string>
#include <vector>
namespace forgearm::hardware {
struct ArmSlot { std::string id; std::shared_ptr<IHardwareDriver> driver; SafetyGate* gate{}; std::vector<double> last_command; };
class ArmGroup {
public:
 explicit ArmGroup(std::size_t maximum_arms=8);
 [[nodiscard]] DriverResult add_arm(std::string id,std::shared_ptr<IHardwareDriver> driver,SafetyGate* gate);
 [[nodiscard]] std::size_t size()const noexcept;
 [[nodiscard]] std::size_t capacity()const noexcept;
 [[nodiscard]] std::vector<std::string> arm_ids()const;
 [[nodiscard]] DriverResult connect_all(const std::vector<DriverConfig>& configs);
 [[nodiscard]] DriverResult enable_all();
 [[nodiscard]] DriverResult command(const std::string& arm_id,const std::vector<double>& target);
 [[nodiscard]] DriverResult stop_all()noexcept;
 [[nodiscard]] DriverResult disconnect_all()noexcept;
private: std::size_t maximum_arms_; std::vector<ArmSlot> arms_;
};
} // namespace forgearm::hardware
