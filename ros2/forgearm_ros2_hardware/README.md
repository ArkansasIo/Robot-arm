# ForgeArm ROS 2 Hardware Plugin Scaffold

This is a ROS 2 `ros2_control` SystemInterface plugin scaffold. It implements the pluginlib loading contract and a mock-only mode. It intentionally **refuses activation when `mock_mode` is not `true`**, and its read/write methods return errors outside mock mode. It does not operate real motors.

## Build in a ROS 2 workspace
Copy/symlink this package into a workspace's `src/`, source the target ROS 2 distribution, then run:
```bash
colcon build --packages-select forgearm_ros2_hardware
source install/setup.bash
```
API compatibility depends on the selected ROS 2 distribution. Review compiler output and the matching distribution's ros2_control docs.

## Mock URDF configuration
Within the robot URDF/Xacro:
```xml
<ros2_control name="ForgeArmMock" type="system">
  <hardware>
    <plugin>forgearm_ros2_hardware/ForgeArmSystem</plugin>
    <param name="mock_mode">true</param>
  </hardware>
  <joint name="joint_1">
    <command_interface name="position"/>
    <state_interface name="position"/>
  </joint>
  <joint name="joint_2">
    <command_interface name="position"/>
    <state_interface name="position"/>
  </joint>
  <joint name="joint_3">
    <command_interface name="position"/>
    <state_interface name="position"/>
  </joint>
</ros2_control>
```

## Turning this into a real driver
A device-specific implementation is still required. Replace the mock-only guard only after adding the exact vendor SDK/protocol, encoder scaling, gear ratio and direction, calibrated limits, stale-feedback handling, command timeout, watchdog, communication-loss behavior, fault recovery, and independently engineered safety functions. Do not use a generic software flag as an emergency stop. Validate with the actual device under a documented risk assessment and controlled test procedure.
