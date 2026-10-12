# ForgeArm — C++23 Robot Arm Simulator

ForgeArm is a dependency-free C++23 project for a **simulated 3-DOF planar robot arm**. Version 0.2 adds scalar motion profiles, workspace analysis, 2D obstacle geometry, simulation state management, five regression suites, and GitHub Actions CI.

> **Safety boundary:** this project is a simulator. It does not drive motors, provide real-time control, or implement safety-rated functions. Do not connect it directly to physical hardware.

## Features
- Forward and inverse kinematics with joint-limit validation
- Trapezoidal scalar trajectory generation with velocity/acceleration limits
- Coarse radial workspace envelope and pose-specific IK check
- 2D segment/circle collision primitives and approximate arm-link collision checks
- Simulation state, joint-space trajectory stepping, stop/reset, and simulated fault state
- CMake C++23 build, five CTest suites, CI workflow, engineering and API documentation

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
- `tests/`: regression tests for kinematics, trajectories, workspace, collision, and simulator state
- `examples/arm_config.toml`: illustrative configuration values; currently documentation only, no parser
- `docs/`: design, research, safety, API, build, testing, roadmap, contribution guide, file index
- `.github/workflows/ci.yml`: automated build and test workflow

## Modeling limitations
The arm model is planar and uses three rotary joints. Default link lengths are 1.0, 0.8, and 0.3 arbitrary units. The radial workspace envelope is coarse; joint limits and tool orientation can further restrict reachability. Collision checking approximates links as line segments with circular clearance and does not include self-collision, swept-volume checking, dynamic obstacles, or uncertainty. The simulator's collision state is not a safety-rated monitor.

## Research and roadmap
See [docs/RESEARCH.md](docs/RESEARCH.md) and [docs/ROADMAP.md](docs/ROADMAP.md). Research topics include inverse kinematics, trajectory generation, motion planning, and robotics safety.

## License
MIT. See [LICENSE](LICENSE).
