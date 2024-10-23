#include "subsystems/Drivetrain.h"

void Drivetrain::initSubsystem() {
  CrcLib::InitializePwmOutput(MOTOR_LEFT_WHEELS);
  CrcLib::InitializePwmOutput(MOTOR_RIGHT_WHEELS, true);
}

void Drivetrain::updateSubsystem() { driveFromJoystick(); }

void Drivetrain::driveFromJoystick() {
  // Make sure the joystick values are above a minimum
  double joystickX = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
  joystickX =
      (fabs(joystickX) < DriveConstants::kMinXInputThreshold) ? 0 : joystickX;

  double joystickY = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
  joystickY =
      (fabs(joystickY) < DriveConstants::kMinYInputThreshold) ? 0 : joystickY;

  drive(joystickX, joystickY);
}

void Drivetrain::drive(int xValue, int yValue) {
  CrcLib::MoveArcade(yValue, xValue, MOTOR_LEFT_WHEELS, MOTOR_RIGHT_WHEELS);
}