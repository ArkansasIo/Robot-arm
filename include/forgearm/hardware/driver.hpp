#pragma once
#include "forgearm/types.hpp"
#include <string>
#include <vector>
namespace forgearm::hardware {
enum class DriverStatus { disconnected, ready, enabled, fault };
struct JointTelemetry { double position{}; double velocity{}; double effort{}; bool valid{false}; };
struct DriverCapabilities { std::size_t joint_count{}; bool position_command{false}; bool velocity_command{false}; bool effort_command{false}; bool feedback{false}; };
struct DriverResult { bool ok{false}; std::string message; };
struct DriverConfig { std::string arm_id; std::vector<std::string> joint_names; double max_position_step_rad{0.05}; };
class IHardwareDriver {
public:
 virtual ~IHardwareDriver()=default;
 [[nodiscard]] virtual std::string name() const=0;
 [[nodiscard]] virtual DriverCapabilities capabilities() const noexcept=0;
 [[nodiscard]] virtual DriverStatus status() const noexcept=0;
 virtual DriverResult connect(const DriverConfig& config)=0;
 virtual DriverResult enable()=0;
 virtual DriverResult read(std::vector<JointTelemetry>& out)=0;
 virtual DriverResult command_position(const std::vector<double>& radians)=0;
 virtual DriverResult stop() noexcept=0;
 virtual void disconnect() noexcept=0;
};
} // namespace forgearm::hardware
