# ForgeArm — C++23 Robot Arm Simulator

ForgeArm is a dependency-free C++23 project for a **simulated 3-DOF planar robot arm**. Version 0.2 expands the original kinematics core with scalar motion profiles, workspace analysis, 2D obstacle geometry, simulation state management, more regression tests, and GitHub Actions CI.

> **Safety boundary:** this project is a simulator. It does not drive motors, provide real-time control, or implement safety-rated functions. Do not connect it directly to physical hardware.

## Features

- Forward and inverse kinematics with joint-limit validation
- Trapezoidal scalar trajectory generation with velocity/acceleration limits
- Coarse radial workspace envelope and pose-specific IK check
- 2D segment/circle collision primitives and approximate arm-link collision checks
- Simulation state, joint-space trajectory stepping, stop/reset, and simulated fault state
- CMake C++23 build, four CTest suites, CI workflow, design/research/API/build/testing docs

## Build

Requirements: CMake 3.20+ and a C++23-capable compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/forgearm_demo
```

On Windows with Visual Studio:
```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\forgearm_demo.exe
```

## Repository layout

- `include/forgearm/`: public types, math, kinematics, trajectories, workspace, collision, simulator APIs
- `src/`: implementations and command-line demo
- `tests/`: regression tests for kinematics, trajectories, workspace, and collision geometry
- `examples/arm_config.toml`: illustrative configuration values; currently documentation only, no parser
- `docs/`: design, research, safety, API, build, testing, roadmap, contribution guide, file index
- `.github/workflows/ci.yml`: build and test workflow

## Important modeling limitations

The arm model is planar and uses three rotary joints. Link lengths default to 1.0, 0.8, and 0.3 arbitrary units. The workspace radial envelope is coarse; joint limits and tool orientation can further restrict reachability. Collision checking approximates links as line segments with circular clearance and does not include self-collision, swept-volume checking, dynamic obstacles, or uncertainty. The simulator's collision state is not a safety-rated monitor.

## Research

See [docs/RESEARCH.md](docs/RESEARCH.md), which links to Modern Robotics educational resources, ROS 2, MoveIt, ISO robot safety standards, and NIST robotics work.

## Next milestones

1. Interactive 2D visualizer.
2. Cartesian trajectory interpolation with IK per sample.
3. Jacobian utilities and singularity detection.
4. Self-collision, swept-volume, and path-planning algorithms.
5. Property-based testing and numerical comparison against a trusted robotics library.

## License

MIT. See [LICENSE](LICENSE).
