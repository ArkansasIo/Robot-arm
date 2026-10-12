# Testing Strategy

CTest runs focused executables for kinematics, trajectory generation, workspace checks, collision geometry, and simulator state transitions.

Coverage includes:
- FK/IK round-trip, unreachable and non-finite targets, invalid link lengths.
- Trajectory start/end conditions, reverse movement, and sampled velocity bounds.
- Workspace radial envelope, bounding-box behavior, and pose-specific IK.
- Segment intersection, circle clearance, and arm-obstacle contact.
- Simulator move/step completion, joint-state updates, reset, and collision fault state.

Run:
```sh
cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

These are software regression tests, not physical validation or safety certification. Add property-based tests and independent numerical cross-checks before production use.
