# ForgeArm — System Design Specification

## Goal
Provide a portable C++23 software foundation for a simulated planar 3R manipulator. The design separates kinematics, scalar trajectory generation, workspace estimates, collision primitives, simulation state, and user interface.

## Functional requirements
| ID | Requirement | Acceptance |
|---|---|---|
| FR-01 | Forward kinematics | Return tool x/y/orientation for joint angles |
| FR-02 | Inverse kinematics | Return a joint solution or explicit failure |
| FR-03 | Joint bounds | Reject out-of-limit candidates |
| FR-04 | Configuration validation | Reject non-finite/non-positive link lengths and invalid bounds |
| FR-05 | Scalar motion profile | Respect requested velocity and acceleration bounds in a profile |
| FR-06 | Workspace estimate | Expose coarse radial envelope and bounding-box checks |
| FR-07 | Collision primitives | Detect 2D segment intersection and segment-circle contact |
| FR-08 | Simulation state | Step joint-space trajectories, reset, stop, and report simulated faults |
| FR-09 | Regression tests | CTest covers kinematics, trajectory, workspace, collision, and simulator |
| NFR-01 | Portability | C++23 and CMake, no required third-party library |
| NFR-02 | Safety boundary | No physical actuator output or safety certification claims |

## Mechanical concept
The model has three revolute joints and rigid links in a plane. Default lengths are 1.0, 0.8, and 0.3 arbitrary units. The base is (0,0), and tool orientation is q1+q2+q3. This is not a fabrication drawing; a physical design requires materials, payload/reach targets, bearings, gearboxes, fasteners, mounting, cable routing, guarding, and structural analysis.

## Software architecture
- `types.hpp`: pose, joint, limit, and configuration types.
- `math.hpp`: 2D vector operations.
- `kinematics.cpp`: FK, analytic IK, and joint-limit validation.
- `trajectory.cpp`: scalar trapezoidal acceleration/cruise/deceleration profile.
- `workspace.cpp`: coarse radial envelope and pose-specific IK query.
- `collision.cpp`: segment/circle geometry and approximate arm links.
- `simulator.cpp`: simulated joint state, profile stepping, stop/reset, and fault status.
- `main.cpp`: deterministic command-line demonstration.
- `tests/`: focused regression suites.
- `.github/workflows/ci.yml`: automated configure/build/test pipeline.

## Inverse kinematics
For target (x,y,φ), wrist centre is wx=x−L3 cosφ and wy=y−L3 sinφ. Compute cos(q2)=(wx²+wy²−L1²−L2²)/(2L1L2). If outside [-1,1] beyond tolerance, the pose is unreachable. Otherwise evaluate q2=±acos(cos(q2)), solve q1 with atan2 terms, and q3=φ−q1−q2. Candidates must satisfy joint limits and pass a forward-kinematics reconstruction check.

## Trajectory profile
The scalar trajectory uses symmetric acceleration and deceleration. If the requested displacement is short, the profile is triangular; otherwise it includes a constant-velocity segment. The simulator creates a separate profile for each joint. This does not guarantee a straight Cartesian path, synchronized acceleration across joints, or collision-free swept motion.

## Workspace and collision limitations
The radial envelope is a coarse geometric bound and does not account for joint limits, tool orientation, or obstacles. Collision geometry approximates each arm link as a line segment with circular clearance. It does not model self-collision, variable link cross-section, swept volume between samples, dynamic obstacles, or measurement uncertainty.

## Units and conventions
- Length uses consistent units; calibrated physical models should use metres.
- Library angles use radians; helpers convert degrees.
- Positive angle is counter-clockwise in the XY plane.
- No dynamics, torque/current model, hardware feedback, or real-time guarantee is implemented.

## Roadmap
1. Add an interactive 2D visualizer.
2. Add Cartesian interpolation with IK per sample and collision-aware path planning.
3. Add Jacobians, singularity metrics, and self-collision/swept-volume checking.
4. Add numerical property tests and comparison against a trusted robotics library.
5. Select hardware only in a separate adapter project with documented safety engineering and validation.
