# ForgeArm Driver Integration Matrix

ForgeArm's portable core accepts implementations of `forgearm::hardware::IHardwareDriver`. The following adapter families are planned as independent plugins. Their configuration examples are intentionally disabled and do not communicate with physical devices.

| Adapter family | Typical link | Scope | Current state |
|---|---|---|---|
| Dynamixel smart servos | USB serial / vendor SDK | Servo discovery, position read/write, torque state | Specification/config scaffold only |
| GRBL / stepper controller | USB serial | G-code or documented controller commands, homing and status | Specification/config scaffold only |
| CAN / CAN-FD drive | CAN interface | Vendor-specific CANopen, CiA 402, or proprietary profile | Specification/config scaffold only |
| MCU bridge (Arduino / ESP32 / Raspberry Pi) | USB serial, Ethernet, GPIO bridge | Explicit framed protocol to a separately validated MCU firmware | Specification/config scaffold only |
| Industrial robot via ROS 2 | Ethernet / ROS 2 middleware | ros2_control SystemInterface plugin | Mock-only scaffold in `ros2/forgearm_ros2_hardware` |

## Important distinction

These are integration targets, not claims of tested hardware support. A transport name is not a sufficient device specification. The exact model, firmware, SDK/protocol version, encoder scaling and direction, homing procedure, drive state machine, watchdog, limits, and safety circuit must be known before an adapter can safely operate hardware.

## Configuration examples

See `examples/controllers/`. All examples set `enabled = false` and `mode = "mock"`. They document intended configuration only; the root project does not yet parse these TOML files automatically.

## Required adapter behavior

Every production adapter must:
- Default to disconnected and disabled.
- Require explicit opt-in to hardware mode and an operator-controlled enable sequence.
- Validate joint count, units, finite values, command limits, and command rate.
- Reject commands on stale or invalid feedback, device fault, timeout, or transport loss.
- Have bounded I/O timeouts and a watchdog/heartbeat where supported.
- Implement stop and disconnect behavior appropriate to the controller, while documenting that software stop is not a safety-rated emergency stop.
- Include protocol unit tests, fault-injection tests, and guarded hardware-in-the-loop tests.
- Never silently fall back from a failed physical driver to a mock driver, or the reverse.

## Multi-arm deployments

Use a unique `arm_id`, independent limits and a distinct transport endpoint for each arm. Shared buses must explicitly map each device ID and guarantee that one arm's fault cannot cause an unsafe command to another. Do not assume eight arms can share a bus or controller without checking device and bandwidth limits.

## How to finish a real adapter

Provide the exact make/model, firmware, controller SDK or protocol documentation, connection type, joint count, encoder/gear-ratio details, and the intended operating environment. These details are needed to replace a configuration scaffold with a device-specific implementation.
