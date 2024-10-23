#pragma once

#include <CrcLib.h>

#include "Constants.h"
#include "Subsystem.h"

class Intake : public Subsystem {
 public:
  void updateSubsystem() override;
  void initSubsystem() override;

 private:
  // output in range [-128, 127]
  void setRollers(int output);
  // output in range [-128, 127]
  void setWinch(int output);

  void runRollersFromInput();
  void runWinchFromInput();

  bool areRollersToggled;
  bool isButtonAlreadyPressed;
};