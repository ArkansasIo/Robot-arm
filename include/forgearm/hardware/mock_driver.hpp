#pragma once
#include "forgearm/hardware/driver.hpp"
#include <mutex>
namespace forgearm::hardware {
// Deterministic mock only. It never opens ports or writes to physical devices.
class MockDriver final:public IHardwareDriver {
public:
 [[nodiscard]] std::string name()const override;
 [[nodiscard]] DriverCapabilities capabilities()const noexcept override;
 [[nodiscard]] DriverStatus status()const noexcept override;
 DriverResult connect(const DriverConfig& config)override;
 DriverResult enable()override;
 DriverResult read(std::vector<JointTelemetry>& out)override;
 DriverResult command_position(const std::vector<double>& radians)override;
 DriverResult stop()noexcept override;
 void disconnect()noexcept override;
private: mutable std::mutex mutex_; DriverStatus status_{DriverStatus::disconnected}; DriverConfig config_{}; std::vector<JointTelemetry> joints_{};
};
} // namespace forgearm::hardware
