# Hardware and Controller Integration

## Status
ForgeArm now has a generic C++ driver interface, a mock driver, an eight-slot arm-group coordinator, and a software command gate. The mock driver never opens a port or sends electrical commands. No vendor-specific physical driver is included because the actual motor/controller model, communication protocol, encoder conventions, limits, and emergency-stop architecture have not been specified.

## Abstraction layers
1. Kinematics and planning produce desired joint states.
2. `IHardwareDriver` defines connect, enable, feedback read, position command, stop, and disconnect.
3. `SafetyGate` checks finite values, joint limits, joint count, and command-step bounds.
4. `ArmGroup` manages up to eight separately identified drivers.
5. A future vendor adapter implements the interface using the manufacturer's documented SDK/protocol.

The software gate is a secondary application check, not a safety-rated function. It cannot replace a physical emergency stop, drive safety functions, interlocks, guarding, certified limits, or risk assessment.

## Eight-arm setup
`examples/arms/arm_01.toml` through `arm_08.toml` provide independent example profiles and unique IDs. They are examples only; the root project does not yet include a TOML parser. Each profile defaults to `driver = "mock"` and `hardware.enabled = false`.

## Adding a vendor driver
- Identify the exact arm, motor drives, firmware, encoder units/direction, gear ratios, supported command mode, bus/serial protocol, and manufacturer SDK.
- Implement a separate driver class; validate packet framing, checksums, timeouts, stale feedback, device faults, and communication loss.
- Require explicit operator enable and a verified safe state; reject commands before enable and after any fault.
- Do not assume the software gate is an emergency stop. Safety functions must be independent and appropriate to the risk assessment.
- Add device-independent tests and vendor hardware-in-the-loop tests under controlled, guarded conditions.
- Review and validate the complete application with a qualified robotics integrator before physical operation.

## ROS 2 integration
ROS 2 `ros2_control` supports dynamically loaded hardware components through `hardware_interface` and `pluginlib`. The exact interface methods and package dependencies depend on the selected ROS 2 distribution. See:
- https://control.ros.org/jazzy/doc/getting_started/getting_started.html
- https://control.ros.org/master/doc/ros2_control/hardware_interface/doc/hardware_interface_types_userdoc.html
- https://github.com/ros-controls/ros2_control/blob/master/hardware_interface/doc/writing_new_hardware_component.rst

This repository's root CMake build does not require ROS 2. A ROS 2 plugin package should be built in a matching ROS 2 workspace, not silently mixed into the portable core build.
