#include "subsystems/Intake.h"

void Intake::initSubsystem() {
  CrcLib::InitializePwmOutput(MOTOR_ROLLERS);
  CrcLib::InitializePwmOutput(MOTOR_WINCH_INTAKE);
}

void Intake::updateSubsystem() {
  runRollersFromInput();
  runWinchFromInput();
}

void Intake::runRollersFromInput() {
  // This works as a toggle and not a press
  if (CrcLib::ReadDigitalChannel(BUTTON::L1)) {
    if (!isButtonAlreadyPressed) {
      isButtonAlreadyPressed = true;
      areRollersToggled = !areRollersToggled;
    }
  } else {
    isButtonAlreadyPressed = false;
  }

  int output = 0;
  if (areRollersToggled) {
    output = IntakeConstants::kRollersOnValue;
  }
  setRollers(output);
}

void Intake::runWinchFromInput() {
  int output = 0;
  if (CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT)) {
    output = IntakeConstants::kWinchOnValue;
  } else if (CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT)) {
    output = -IntakeConstants::kWinchOnValue;
  }
  setWinch(output);
}

void Intake::setRollers(int output) {
  CrcLib::SetPwmOutput(MOTOR_ROLLERS, output);
}

void Intake::setWinch(int output) {
  CrcLib::SetPwmOutput(MOTOR_WINCH_INTAKE, output);
}