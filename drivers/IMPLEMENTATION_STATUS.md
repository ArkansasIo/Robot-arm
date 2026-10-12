# Driver Implementation Status

- [x] Common C++ hardware interface exists in `include/forgearm/hardware/driver.hpp`.
- [x] Mock driver and software safety gate exist in the core.
- [x] Eight example arm profiles exist under `examples/arms/`.
- [x] Configuration-only examples exist for Dynamixel, GRBL/stepper, CAN, MCU bridge, and ROS 2.
- [x] ROS 2 plugin scaffold is explicitly mock-only.
- [ ] TOML parser and validated configuration loader.
- [ ] Device-specific Dynamixel driver (exact model/SDK required).
- [ ] Device-specific GRBL/stepper adapter (exact firmware and machine suitability required).
- [ ] CAN/CAN-FD adapter (exact drive and protocol required).
- [ ] MCU bridge implementation plus independently validated firmware.
- [ ] Vendor-specific industrial robot adapter / non-mock ros2_control implementation.
- [ ] Protocol-level tests, timeout/fault injection, and hardware-in-the-loop tests.
- [ ] System safety review for each physical robot deployment.

No physical controller should be considered supported until its adapter is implemented, built, tested against the manufacturer's documentation, and validated with the target hardware under controlled safeguards.
