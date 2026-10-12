# Safety Boundary and Physical-Deployment Checklist
ForgeArm is a software-only kinematic demonstration and has no certified safety functions.
A successful IK result establishes only geometric consistency under this model and joint limits. It does not check collision, structural strength, payload, torque, braking, speed, thermal limits, wiring, or human exposure.
Before physical operation:
- Define intended use, payload, reach, speeds, and foreseeable misuse.
- Conduct a documented risk assessment for the complete application/cell.
- Select appropriate guarding, interlocks, emergency-stop and protective-stop equipment.
- Use the manufacturer's supported controller interface; do not bit-bang actuators from this demo.
- Keep safety-rated controls independent from non-safety application code.
- Configure and validate limits against actual hardware.
- Add watchdogs, communication-loss handling, fault states, and controlled stopping.
- Test at reduced speed in a guarded, controlled setting with qualified personnel.
- Obtain qualified engineering/integrator review and comply with applicable laws and standards.
Do not use this project as a medical, life-critical, or safety-rated controller.
