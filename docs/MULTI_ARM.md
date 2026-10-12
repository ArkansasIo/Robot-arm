# Multi-Arm Coordination

ForgeArm's `ArmGroup` registers independent driver instances and supports up to eight arm IDs by default. Each registered arm has its own driver and safety gate.

## Available operations
- Register a unique arm ID and driver.
- Connect configured drivers.
- Enable all registered drivers.
- Send a bounded joint-position command to one arm.
- Stop or disconnect all drivers.
- Query registered IDs and group capacity.

## Current limitations
- This is not synchronized multi-arm motion planning.
- There is no shared-cell collision model, work-cell reservation, coordinated trajectory clock, inter-arm force control, or distributed fault recovery.
- Drivers must return valid joint feedback before position commands are accepted.
- Mock drivers are the only included implementation. No physical bus or actuator is addressed.

## Coordinated-motion requirements for a future version
1. Common monotonic clock and trajectory time base.
2. Collision checking across all arm links and workpieces.
3. Joint-state freshness and clock-skew monitoring.
4. A defined safe-stop policy for one-arm faults and whole-cell faults.
5. Network/bus latency and loss testing.
6. Independent safety functions for the complete cell.
