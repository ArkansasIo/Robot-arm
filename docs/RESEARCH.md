# Research Notes: Robot Arm Design and Software
Prepared: 2026-10-12. Scope: research guide for an educational kinematic simulator, not certification or an exhaustive literature review.
## Research starting points
1. **Modern Robotics — Northwestern University.** Rigid-body transformations, kinematics, Jacobians, dynamics, and motion planning. https://modernrobotics.northwestern.edu/
2. **ROS 2 documentation.** Robotics middleware, node interfaces, integration, and simulation. https://docs.ros.org/
3. **MoveIt documentation.** Motion-planning infrastructure, robot models, collision-aware planning, and controller integration. https://moveit.picknik.ai/
4. **ISO 10218 series.** Industrial robot and robot application/cell safety. Consult the applicable current edition and a qualified integrator. https://www.iso.org/
5. **ISO/TS 15066.** Guidance for collaborative industrial robot applications; collaborative does not mean inherently safe. https://www.iso.org/
6. **NIST robotics research.** Robot performance, measurement, manufacturing, and automation. https://www.nist.gov/
## Design implications
- Treat FK/IK as a math module, not a motor driver.
- Keep geometry and joint limits explicit in configuration.
- Fail closed on invalid or unreachable targets.
- Check candidates by recomputing FK.
- Add collision detection before path planning.
- Apply dynamics-aware time parameterization before executing trajectories.
- Keep emergency stops, interlocks, protective stops, and safety-rated monitoring independent from general-purpose application logic.
## Limitations
No arbitrary 3D transforms, DH chain, Jacobian-based IK, singularity analysis, dynamics, torque/current limits, collision checking, trajectory generation, encoder feedback, network communications, or hardware drivers. No physical hardware validation has been performed. Confirm latest source editions before commercial or regulated deployment.
## Verification checklist
- [ ] Independently validate FK equations.
- [ ] Test singular and near-singular poses.
- [ ] Test both IK branches and joint-limit edges.
- [ ] Validate using calibrated geometry and measured poses.
- [ ] Document payload, reach, speed, use case, and risk assessment.
