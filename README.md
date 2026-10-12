# ForgeArm — C++23 Robot Arm Simulator

A portable, dependency-free C++23 starter project for a simulated 3-DOF planar robot arm. Features forward kinematics, inverse kinematics, joint-limit validation, regression tests, and engineering design/research/safety documents.

## Build

Requirements: C++23 compiler and CMake 3.20+.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
./build/forgearm_demo
```

## Layout

- `include/forgearm/` — API and types
- `src/` — kinematics implementation and CLI demo
- `tests/` — regression tests
- `docs/DESIGN.md` — engineering design specification
- `docs/RESEARCH.md` — research guide and references
- `docs/SAFETY.md` — physical deployment safety boundary
- `docs/ARCHITECTURE.svg` — system architecture diagram

Simulation only: this project does not operate motors or implement safety-rated control. Do not connect it directly to physical robot hardware.

## Kinematic model

Three revolute joints in a plane. The tool orientation is `q1 + q2 + q3`. IK subtracts the final tool link, evaluates elbow-up/down solutions, checks joint limits, then verifies candidates using FK.

## License

MIT.