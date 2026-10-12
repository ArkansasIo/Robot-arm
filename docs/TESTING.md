# Testing Strategy

CTest runs separate executables for kinematics, trajectory generation, workspace checks, and collision geometry.

Coverage includes FK/IK round-trip, unreachable and non-finite targets, invalid link lengths, trajectory endpoints and velocity bounds, workspace envelopes, segment intersection, circle clearance, and arm-obstacle contact.

Run:
```sh
cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

These are software regression tests, not physical validation or safety certification. Add property-based tests and independent numerical cross-checks before production use.
