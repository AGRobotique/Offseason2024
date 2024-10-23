#pragma once

#include <CrcLib.h>

#include "Constants.h"
#include "Subsystem.h"

class Drivetrain : public Subsystem {
 public:
  void updateSubsystem() override;
  void initSubsystem() override;

 private:
  // xValue and yValue in range [-128, 127]
  void drive(int xValue, int yValue);
  void driveFromJoystick();
};