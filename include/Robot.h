#pragma once

#include <CrcLib.h>

#include "Constants.h"
#include "Subsystem.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Lift.h"
#include "subsystems/Shooter.h"

class Robot {
 public:
  Robot();
  void initRobot();
  void updateRobot();
  ~Robot();

 private:
  Subsystem** subsystems;
};
