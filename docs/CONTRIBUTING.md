# Contributing

1. Keep the core dependency-free unless a dependency is justified in an architecture note.
2. Preserve C++23 and enable compiler warnings.
3. Add regression tests for new behavior and edge cases.
4. Document units, coordinate conventions, tolerances, and limitations.
5. Never describe simulation checks as safety-certified.
6. Run CMake build and CTest before submitting changes.
7. Keep future hardware-specific code isolated behind an adapter; do not add motor output to the kinematics library.
