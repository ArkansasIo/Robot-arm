# File Index

- `include/forgearm/types.hpp`: poses, joints, limits, and arm configuration.
- `include/forgearm/math.hpp`: 2D vector and distance utilities.
- `include/forgearm/kinematics.hpp`: kinematics API.
- `include/forgearm/trajectory.hpp`: scalar motion profile API.
- `include/forgearm/workspace.hpp`: workspace envelope and target reachability.
- `include/forgearm/collision.hpp`: 2D collision primitives and arm link geometry.
- `include/forgearm/simulator.hpp`: simulation state and stepping API.
- `src/kinematics.cpp`: forward/inverse kinematics.
- `src/trajectory.cpp`: trapezoidal profile.
- `src/workspace.cpp`: workspace calculations.
- `src/collision.cpp`: segment/circle geometry.
- `src/simulator.cpp`: state transitions and trajectory stepping.
- `src/main.cpp`: CLI demo.
- `tests/`: regression tests.
- `examples/arm_config.toml`: illustrative settings; not parsed yet.
- `docs/`: design, research, safety, API, build, testing, roadmap, and contribution documents.
