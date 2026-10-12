# Controller Configuration and Multi-Transport Plan

## Goal

ForgeArm is intended to host several independent hardware adapters behind `IHardwareDriver`, including smart servos, stepper controllers, CAN drives, MCU bridges, and industrial robots exposed through ROS 2. These adapters must remain isolated from kinematics and planning.

## Configuration status

The TOML files under `examples/controllers/` are human-readable examples only. ForgeArm does not yet include a TOML parser or configuration loader. The files deliberately use `mode = "mock"` and `enabled = false`; placeholder port/interface/protocol values are not usable hardware settings.

| Profile | Example file | Intended interface |
|---|---|---|
| Dynamixel | `examples/controllers/dynamixel.toml` | USB serial and the exact supported servo SDK/protocol |
| GRBL / stepper | `examples/controllers/grbl.toml` | Serial controller protocol; verify suitability for articulated arms |
| CAN drive | `examples/controllers/can_drive.toml` | CAN/CAN-FD and a named vendor protocol |
| MCU bridge | `examples/controllers/mcu_bridge.toml` | Versioned, checksummed application protocol |
| ROS 2 industrial | `examples/controllers/ros2_industrial.toml` | Matching ROS 2 distribution and ros2_control plugin |

The first four are not implemented physical drivers. The ROS 2 package under `ros2/forgearm_ros2_hardware/` is also mock-only and intentionally refuses physical mode.

## Proposed adapter layering

1. `IHardwareDriver`: common connect, enable, read, command, stop and disconnect API.
2. Device-specific driver: vendor SDK or documented wire protocol.
3. Transport: serial, CAN, Ethernet, or ROS 2 middleware with bounded I/O and explicit timeout behavior.
4. `SafetyGate`: secondary software checks before commands reach the driver.
5. `ArmGroup`: independent arm IDs, driver instances and limits.

Keep the transport and protocol code testable without hardware. Inject a fake transport in tests so malformed frames, timeouts, stale telemetry, bad checksums, disconnects, and drive faults can be exercised deterministically.

## Multi-arm configuration

Each arm requires a unique ID, unique joint mapping, individual calibrated limits, and an explicit endpoint/device-ID mapping. Sharing one physical controller between several arms requires a documented multiplexing strategy. Never broadcast commands to unknown device IDs. On one arm's communication fault, the system should stop that arm and apply a documented system-level policy to the remaining arms.

## Safety boundary

Software checks are not safety-rated and do not replace a physical emergency stop, protective guarding, interlocks, certified drive safety functions, or a formal risk assessment. Do not connect actuators or run motion tests until the complete robot system has been reviewed and tested under appropriate safeguards.

## Information needed for implementation

For each target, supply exact manufacturer and model, firmware version, SDK/protocol version, electrical interface, joint count, encoder units and direction, gear ratio, position/velocity limits, homing method, drive enable state machine, feedback freshness requirements, watchdog behavior, and emergency-stop architecture. The adapter must be designed against those details rather than guessing from the connector type.
