# Research Notes: Robot Arm Design and Software

**Prepared:** 2026-10-12  
**Scope:** research guide for an educational C++23 kinematics and motion simulator. This is not a complete literature review, physical validation report, or safety certification.

## Reference topics and authoritative starting points

1. **Modern Robotics — Northwestern University.** Educational materials cover rigid-body transformations, forward/inverse kinematics, Jacobians, dynamics, trajectory generation, and motion planning. The book's Chapter 6 discusses inverse kinematics; Chapter 9 covers trajectory generation; Chapter 10 covers motion planning.  
   https://modernrobotics.northwestern.edu/nu-gm-book-resource/  
   https://modernrobotics.northwestern.edu/nu-gm-book-resource/inverse-kinematics-of-open-chains/  
   https://modernrobotics.northwestern.edu/nu-gm-book-resource/9-1-and-9-2-point-to-point-trajectories-part-1-of-2/

2. **ROS 2 documentation.** Useful when considering robotics middleware, node interfaces, simulation, and integration. Middleware is not a safety certification.  
   https://docs.ros.org/

3. **MoveIt documentation.** Motion-planning infrastructure commonly used with ROS; review robot model configuration, planning-scene collision checking, trajectory execution, and controller integration.  
   https://moveit.picknik.ai/

4. **ISO 10218 series.** Industrial robot and robot-application/cell safety requirements. Obtain the applicable current edition and have a qualified integrator determine applicability.  
   https://www.iso.org/

5. **ISO/TS 15066.** Reference for collaborative industrial robot applications. Collaborative operation does not mean inherently safe; the entire application and risk assessment matter.  
   https://www.iso.org/

6. **NIST robotics research.** Work on robot performance, measurement, manufacturing, and automation.  
   https://www.nist.gov/

7. **C++23 language/library reference.** Check compiler and standard-library support when selecting build environments.  
   https://en.cppreference.com/w/cpp/23

## Design implications
- Treat FK/IK as a mathematical module, not a motor driver.
- Keep geometry and joint limits explicit in configuration.
- Fail closed on invalid or unreachable targets.
- Verify IK candidates by recomputing FK.
- Add collision checking before path planning, and account for the difference between point checks and swept-volume checks.
- Add dynamics-aware time parameterization before executing trajectories on any physical platform.
- Keep emergency stops, interlocks, protective stops, and safety-rated monitoring independent from general-purpose application logic.
- Document units, coordinate frames, tolerances, model calibration, and test conditions.

## Current implementation and gaps
Implemented: planar 3R FK/IK, joint-limit checks, scalar trapezoidal profiles, coarse workspace envelope, 2D segment/circle collision helpers, simulated joint-space stepping, and regression tests.

Not implemented: arbitrary 3D transforms, DH chains, Jacobian-based IK, singularity analysis, dynamics, torque/current limits, self-collision, swept-volume checking, Cartesian path planning, structured configuration parsing, encoder feedback, network communications, or hardware drivers. No physical hardware validation has been performed.

## Verification checklist
- [ ] Independently validate FK and IK equations.
- [ ] Test singular and near-singular poses, both IK branches, and joint-limit edges.
- [ ] Test trajectory continuity and constraints at phase boundaries.
- [ ] Test collision cases including tangency, degenerate segments, and obstacle clearances.
- [ ] Validate with calibrated dimensions and measured poses.
- [ ] Define payload, reach, speed, environment, and intended use.
- [ ] Conduct documented risk assessment and application-level validation before physical motion.
