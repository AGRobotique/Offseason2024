#pragma once

#include <CrcLib.h>

#include "Constants.h"
#include "Subsystem.h"

class Lift : public Subsystem {
 public:
  void updateSubsystem() override;
  void initSubsystem() override;

 private:
  // output in range [-128, 127]
  void setAgitator(int output);
  // output in range [-128, 127]
  void setElevator(int output);

  void runAgitatorFromInput();
  void runElevatorFromInput();
};