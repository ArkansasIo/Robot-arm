# ForgeArm — System Design Specification
## Goal
Provide a compact, portable C++23 foundation for exploring planar manipulator geometry. This software separates mathematical kinematics from interfaces and hardware.
## Requirements
| ID | Requirement | Acceptance |
|---|---|---|
| FR-01 | Compute 3-DOF end-effector pose | Forward kinematics returns x/y/orientation |
| FR-02 | Solve inverse kinematics | Return solution or explicit failure |
| FR-03 | Enforce joint bounds | Reject out-of-limit candidates |
| FR-04 | Validate configuration | Reject non-positive lengths or invalid bounds |
| FR-05 | Build using C++23 | CMake produces demo and test targets |
| FR-06 | Regression tests | CTest covers FK/IK, unreachable target, invalid input |
## Mechanical concept
The planar serial arm has three rotary joints and three rigid links. Default lengths are 1.0, 0.8, and 0.3 arbitrary units. Base origin is (0,0). Tool orientation is q1+q2+q3. This is not a fabrication drawing; physical construction requires material, load, bearing, gearbox, mounting, cable, guarding, and structural analysis.
## Software architecture
- `types.hpp`: pose, joint, configuration value types and unit conversion.
- `kinematics.cpp`: configuration validation, FK, IK and joint-limit checks.
- `main.cpp`: deterministic demonstration.
- `test_kinematics.cpp`: regression tests.
## Inverse kinematics
For target (x,y,φ), wrist centre is wx=x−L3 cosφ and wy=y−L3 sinφ. Compute cos(q2)=(wx²+wy²−L1²−L2²)/(2L1L2). If outside [-1,1] beyond tolerance the pose is unreachable. Otherwise evaluate q2=±acos(cos(q2)), solve q1 using atan2 terms and q3=φ−q1−q2. Candidates must satisfy joint limits and pass a forward-kinematics reconstruction check.
## Units and conventions
- Length is a consistent selected unit; metres are recommended for calibrated hardware.
- API angles are radians; conversion helpers are included.
- Positive angle is counter-clockwise in XY plane.
- No velocity, torque, inertia or dynamics model exists yet.
## Roadmap
1. Trajectory interpolation with velocity/acceleration limits.
2. Collision checking and 2D visualization.
3. Dynamics and simulation integration.
4. Hardware adapter only after selecting a specific robot/vendor interface.
5. Risk assessment and validation before physical motion.
