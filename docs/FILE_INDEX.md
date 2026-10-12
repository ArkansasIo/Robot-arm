# File Index

## Core
- `include/forgearm/types.hpp`: poses, joints, limits, arm config.
- `include/forgearm/math.hpp`: 2D vector utilities.
- `include/forgearm/kinematics.hpp`, `src/kinematics.cpp`: FK/IK.
- `include/forgearm/trajectory.hpp`, `src/trajectory.cpp`: scalar trapezoidal profiles.
- `include/forgearm/workspace.hpp`, `src/workspace.cpp`: workspace bounds and IK queries.
- `include/forgearm/collision.hpp`, `src/collision.cpp`: 2D collision geometry.
- `include/forgearm/simulator.hpp`, `src/simulator.cpp`: simulation state and stepping.

## Hardware and multiple arms
- `include/forgearm/hardware/driver.hpp`: vendor-driver interface contract.
- `include/forgearm/hardware/safety_gate.hpp`, `src/hardware/safety_gate.cpp`: application-level command checks.
- `include/forgearm/hardware/mock_driver.hpp`, `src/hardware/mock_driver.cpp`: no-hardware test driver.
- `include/forgearm/hardware/arm_group.hpp`, `src/hardware/arm_group.cpp`: arm registry and up-to-eight-arm coordination shell.
- `tests/test_hardware.cpp`: mock driver and command-gate regression test.
- `examples/arms/arm_01.toml` through `arm_08.toml`: separate arm profiles; not yet parsed by the app.
- `examples/controllers/`: disabled configuration examples for Dynamixel, GRBL/stepper, CAN, MCU bridge, and ROS 2.
- `drivers/README.md`: multi-controller integration matrix and adapter requirements.
- `drivers/IMPLEMENTATION_STATUS.md`: implemented scaffolding versus work remaining.
- `ros2/forgearm_ros2_hardware/`: separate ROS 2 plugin scaffold; mock-only until a vendor transport is implemented.

## Tests
- `tests/test_kinematics.cpp`
- `tests/test_trajectory.cpp`
- `tests/test_workspace.cpp`
- `tests/test_collision.cpp`
- `tests/test_simulator.cpp`
- `tests/test_hardware.cpp`

## Documentation and automation
- `docs/DESIGN.md`, `docs/RESEARCH.md`, `docs/SAFETY.md`
- `docs/HARDWARE.md`, `docs/DRIVER_PLUGIN_CONTRACT.md`, `docs/MULTI_ARM.md`
- `docs/CONTROLLER_CONFIGURATION.md`: controller families, config status, and safety boundary.
- `docs/API.md`, `docs/BUILD.md`, `docs/TESTING.md`, `docs/ROADMAP.md`, `docs/CONTRIBUTING.md`, `docs/FILE_INDEX.md`
- `.github/workflows/ci.yml`: portable core CI.
