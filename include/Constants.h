#pragma once

#define MOTOR_LEFT_WHEELS CRC_PWM_1
#define MOTOR_RIGHT_WHEELS CRC_PWM_2

#define MOTOR_CONVEYOR CRC_PWM_3
#define MOTOR_WHEELS_SHOOTER CRC_PWM_5
#define MOTOR_ROTATION_TURRET CRC_PWM_6
#define SERVO_SLIDER_TURRET CRC_PWM_9

#define MOTOR_ROLLERS CRC_PWM_4
#define MOTOR_WINCH_INTAKE CRC_PWM_7

#define MOTOR_ELEVATOR CRC_PWM_8
#define SERVO_AGITATOR CRC_PWM_10

namespace RobotConstants {
constexpr int kNumberOfSubsystems = 1;
constexpr int kAnalogChannelMaxValue = 127;
}  // namespace RobotConstants

namespace DriveConstants {
constexpr int kMinXInputThreshold =
    0.05 * RobotConstants::kAnalogChannelMaxValue;
constexpr int kMinYInputThreshold =
    0.05 * RobotConstants::kAnalogChannelMaxValue;
}  // namespace DriveConstants

namespace ShooterConstants {
constexpr int kMinPulseWidthTurretServo = 500;
constexpr int kMaxPulseWidthTurretServo = 2500;
constexpr int kConveyorOnValue = 125;
constexpr int kWheelsOnValue = 125;
constexpr double kTurretSensitivityMultiplier = 1.0 / 1.5;
constexpr int kMinJoystickValueSlider = 100;
constexpr double kIncrementFactorSlider = 1.0 / 120.0;
}  // namespace ShooterConstants

namespace IntakeConstants {
constexpr int kRollersOnValue = 125;
constexpr int kWinchOnValue = 125;
}  // namespace IntakeConstants

namespace LiftConstants {
constexpr int kMinPulseWidthAgitatorServo = 500;
constexpr int kMaxPulseWidthAgitatorServo = 2500;
constexpr int kMinTriggerValueAgitator = 100;
constexpr int kElevatorOnValue = 125;
}  // namespace LiftConstants