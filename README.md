# ForgeArm — C++23 Robot Arm Simulator

ForgeArm is a modular C++23 project for simulating a planar 3-DOF robot arm and developing hardware adapters. The portable core includes kinematics, scalar motion profiles, workspace estimates, collision primitives, simulation state, a driver abstraction, software command checks, and an eight-arm group coordinator.

> **Physical hardware warning:** the included drivers are mocks. The ROS 2 plugin scaffold refuses activation unless configured for mock mode. No vendor-specific real motor driver or safety-rated control function is included.

## Features
- Forward/inverse kinematics and joint-limit validation
- Trapezoidal scalar motion profile
- Workspace estimates and 2D segment/circle collision geometry
- Simulator with joint-space stepping, reset, stop, and simulated faults
- `IHardwareDriver` abstraction, mock driver, command gate, and multi-arm coordinator
- Eight separate example arm profiles under `examples/arms/`
- Disabled controller configuration examples for Dynamixel, GRBL/stepper, CAN, MCU bridges, and ROS 2 under `examples/controllers/`
- ROS 2 `ros2_control` plugin scaffold under `ros2/forgearm_ros2_hardware/`
- Six CTest suites and GitHub Actions CI

## Build portable core
Requirements: CMake 3.20+ and a C++23-capable compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/forgearm_demo
```

## Hardware abstraction and ROS 2
Read [docs/HARDWARE.md](docs/HARDWARE.md), [docs/DRIVER_PLUGIN_CONTRACT.md](docs/DRIVER_PLUGIN_CONTRACT.md), [docs/MULTI_ARM.md](docs/MULTI_ARM.md), and [docs/CONTROLLER_CONFIGURATION.md](docs/CONTROLLER_CONFIGURATION.md). The [driver matrix](drivers/README.md) tracks integration targets and their current status. The ROS 2 package has separate build requirements; see [its README](ros2/forgearm_ros2_hardware/README.md).

The controller profiles are documentation/configuration examples only; the root project does not yet parse these TOML files. Physical drivers require exact device models, firmware, vendor SDK/protocol, encoder conventions, electrical interfaces, and safety architecture. Do not enable physical operation by simply changing a mock flag. The software command gate is not a safety-rated function.

## Repository layout
- `include/forgearm/`: types, math, kinematics, trajectories, workspace, collision, simulator, hardware interfaces
- `src/`: portable implementation
- `tests/`: regression suites
- `examples/arms/`: eight independent sample arm profiles (mock-only)
- `examples/controllers/`: disabled controller configuration examples
- `drivers/`: integration matrix and adapter implementation status
- `ros2/forgearm_ros2_hardware/`: ROS 2 plugin scaffold, mock mode only
- `docs/`: design, research, hardware, multi-arm, API, testing, and safety documents

## Research
See [docs/RESEARCH.md](docs/RESEARCH.md) and ROS 2's [hardware interface documentation](https://control.ros.org/jazzy/doc/getting_started/getting_started.html).

## License
MIT. See [LICENSE](LICENSE).
