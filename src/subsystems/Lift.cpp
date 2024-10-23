#include "subsystems/Lift.h"

void Lift::initSubsystem() {
  CrcLib::InitializePwmOutput(MOTOR_ELEVATOR);
  CrcLib::InitializePwmOutput(SERVO_AGITATOR,
                              LiftConstants::kMinPulseWidthAgitatorServo,
                              LiftConstants::kMaxPulseWidthAgitatorServo);
}

void Lift::updateSubsystem() {
  runAgitatorFromInput();
  runElevatorFromInput();
}

void Lift::runAgitatorFromInput() {
  // Defaut value
  int output = 68;
  // If not pressed, agitate
  if (CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R) <
      LiftConstants::kMinTriggerValueAgitator) {
    // Basically a sinus, mapped to a range of -90 to -10
    output =
        map(1000 * sin((float)millis() / (float)150), -1000, 1000, -90, -10);
  }
  setAgitator(output);
}

void Lift::runElevatorFromInput() {
  int output = 0;
  if (CrcLib::ReadDigitalChannel(BUTTON::ARROW_UP)) {
    output = LiftConstants::kElevatorOnValue;
  } else if (CrcLib::ReadDigitalChannel(BUTTON::ARROW_DOWN)) {
    output = -LiftConstants::kElevatorOnValue;
  }
  setElevator(output);
}

void Lift::setAgitator(int output) {
  CrcLib::SetPwmOutput(SERVO_AGITATOR, output);
}

void Lift::setElevator(int output) {
  CrcLib::SetPwmOutput(MOTOR_ELEVATOR, output);
}