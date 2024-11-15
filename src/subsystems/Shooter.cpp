#include "subsystems/Shooter.h"

void Shooter::initSubsystem() {
  CrcLib::InitializePwmOutput(MOTOR_CONVEYOR);
  CrcLib::InitializePwmOutput(MOTOR_WHEELS_SHOOTER);
  CrcLib::InitializePwmOutput(MOTOR_ROTATION_TURRET);
  CrcLib::InitializePwmOutput(SERVO_SLIDER_TURRET,
                              ShooterConstants::kMinPulseWidthTurretServo,
                              ShooterConstants::kMaxPulseWidthTurretServo);
  isShooterToggled = false;
  isButtonAlreadyPressed = false;
}

void Shooter::updateSubsystem() {
  runConveyorFromInput();
  rotateTurretFromInput();
  runShooterWheelsFromInput();
  runSliderFromInput();
}

void Shooter::runConveyorFromInput() {
  int output = 0;
  if (CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP)) {
    output = ShooterConstants::kConveyorOnValue;
  } else if (CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN)) {
    output = -ShooterConstants::kConveyorOnValue;
  }
  setConveyor(output);
}

void Shooter::rotateTurretFromInput() {
  setRotationTurret(CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X) *
                    ShooterConstants::kTurretSensitivityMultiplier);
}

void Shooter::runShooterWheelsFromInput() {
  // Toggle and not press
  if (CrcLib::ReadDigitalChannel(BUTTON::R1)) {
    if (!isButtonAlreadyPressed) {
      isButtonAlreadyPressed = true;
      isShooterToggled = !isShooterToggled;
    }
  } else {
    isButtonAlreadyPressed = false;
  }

  int output = 0;
  if (isShooterToggled) {
    output = -ShooterConstants::kWheelsOnValue;
  }
  setShooterWheels(output);
}

void Shooter::runSliderFromInput() {
  int joystickValue = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);
  // If joystick value greater than a minimum
  if (fabs(joystickValue) > ShooterConstants::kMinJoystickValueSlider) {
    // Add to the current angle
    sliderAngle += static_cast<int>(joystickValue *
                                    ShooterConstants::kIncrementFactorSlider);
    // Make sure it stays within bounds accepted for servos
    if (sliderAngle < -128) {
      sliderAngle = -128;
    } else if (sliderAngle > 127) {
      sliderAngle = 127;
    }
  }
  setSlider(sliderAngle);
}

void Shooter::setConveyor(int output) {
  CrcLib::SetPwmOutput(MOTOR_CONVEYOR, output);
}

void Shooter::setRotationTurret(int output) {
  CrcLib::SetPwmOutput(MOTOR_ROTATION_TURRET, output);
}

void Shooter::setShooterWheels(int output) {
  CrcLib::SetPwmOutput(MOTOR_WHEELS_SHOOTER, output);
}

void Shooter::setSlider(int output) {
  CrcLib::SetPwmOutput(SERVO_SLIDER_TURRET, output);
}