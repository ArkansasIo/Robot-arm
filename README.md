# ForgeArm — C++23 Robot Arm Simulator

ForgeArm is a modular C++23 project for simulating a planar 3-DOF robot arm and developing hardware adapters. The portable core includes kinematics, scalar motion profiles, workspace estimates, collision primitives, simulation state, a driver abstraction, software command checks, and an eight-arm group coordinator.

> **Physical hardware warning:** the included drivers are mocks. The ROS 2 plugin scaffold refuses activation unless explicitly configured for mock mode. No vendor-specific real motor driver or safety-rated control function is included.

## Features
- Forward/inverse kinematics and joint-limit validation
- Trapezoidal scalar motion profile
- Workspace estimates and 2D segment/circle collision geometry
- Simulator with joint-space stepping, reset, stop, and simulated faults
- `IHardwareDriver` abstraction, mock driver, command gate, and multi-arm coordinator
- Eight separate example arm profiles under `examples/arms/`
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
Read [docs/HARDWARE.md](docs/HARDWARE.md), [docs/DRIVER_PLUGIN_CONTRACT.md](docs/DRIVER_PLUGIN_CONTRACT.md), and [docs/MULTI_ARM.md](docs/MULTI_ARM.md). The ROS 2 package has a separate build and dependency requirements; see [its README](ros2/forgearm_ros2_hardware/README.md).

A real device adapter cannot be completed responsibly without the exact arm/controller model, vendor SDK or protocol, encoder conventions, electrical interfaces, and safety architecture. Do not set a mock flag to operate real hardware. The software command gate is not a safety-rated function.

## Repository layout
- `include/forgearm/`: types, math, kinematics, trajectories, workspace, collision, simulator, hardware interfaces
- `src/`: portable implementation
- `tests/`: regression suites
- `examples/arms/`: eight independent sample profiles (mock-only)
- `ros2/forgearm_ros2_hardware/`: ROS 2 plugin scaffold, mock mode only
- `docs/`: design, research, hardware, multi-arm, API, testing, and safety documents

## Research
See [docs/RESEARCH.md](docs/RESEARCH.md) and ROS 2's [hardware interface documentation](https://control.ros.org/jazzy/doc/getting_started/getting_started.html).

## License
MIT. See [LICENSE](LICENSE).
