# Development Roadmap

## Version 0.2 — Geometry and motion
- [x] Scalar trapezoidal motion profile.
- [x] Coarse workspace envelope.
- [x] 2D segment and circle collision primitives.
- [x] Basic simulated state and joint-space stepping.
- [ ] Interactive graphical visualizer.
- [ ] Joint velocity/acceleration telemetry.

## Version 0.3 — Planning
- [ ] Collision-aware path search in joint space.
- [ ] Self-collision and swept-volume checking.
- [ ] Cartesian interpolation with IK per sample.
- [ ] Singularity detection and Jacobian utilities.

## Version 0.4 — Validation
- [ ] Property-based tests and sanitizer CI.
- [ ] Model comparison against a trusted robotics implementation.
- [ ] Calibrated geometry import and structured configuration parser.
- [ ] Numerical tolerance and performance report.

Real motor control, real-time guarantees, safety-rated functions, and deployment certification are out of scope.
