# Driver Plugin Contract

Implement `forgearm::hardware::IHardwareDriver` in a separate module for a specific device family.

Required methods:
- `name()`: stable human-readable driver identifier.
- `capabilities()`: supported command modes, feedback, and joint count.
- `status()`: disconnected, ready, enabled, or fault.
- `connect(config)`: validate device settings and establish communications.
- `enable()`: enable only after external safety preconditions have been confirmed.
- `read(out)`: return fresh joint telemetry with per-joint validity.
- `command_position(radians)`: validate size and finite values, then use the documented vendor protocol.
- `stop()`: request the vendor-supported stop action; do not claim this is an emergency stop unless independently safety-rated.
- `disconnect()`: release communication resources and disable application commands.

Never silently clamp invalid commands, hide stale feedback, or convert communication errors into successful results. Use timeouts, watchdogs, explicit fault states, and tests. Physical behavior depends on the device and its manufacturer documentation.
