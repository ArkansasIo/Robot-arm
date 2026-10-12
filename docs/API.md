# API Reference

All angles in the C++ API use radians. Link lengths must use consistent units. Defaults are illustrative.

## Kinematics
- `Kinematics(config)` validates positive finite link lengths and joint bounds.
- `forward(JointAngles)` returns tool `Pose2D`.
- `inverse(Pose2D)` returns an `IkResult` with explicit failure status.
- `within_limits(JointAngles)` checks the configured bounds.

## Trajectory
`TrapezoidalTrajectory(start, finish, MotionLimits)` creates a symmetric scalar acceleration/cruise/deceleration profile. Sampling clamps to endpoints outside its time interval. Independent joint profiles do not guarantee a straight Cartesian path.

## Workspace
`radial_envelope()` is a coarse geometric envelope. Joint limits and tool orientation may make a point within the envelope unreachable. Use `pose_has_ik()` for a pose-specific kinematics check.

## Collision
Segment/circle tests approximate each link as a line segment with optional circular clearance. Self-collision, link-specific widths, dynamic obstacles, swept-volume checks, and uncertainty are not modeled.

## Simulator
`Simulator` maintains simulated joints and tool pose, creates per-joint profiles, and advances with `step(dt)`. A detected obstacle intersection faults the simulation. This is not a safety-rated collision monitor.
