#pragma once

#include <CrcLib.h>

#include "Constants.h"
#include "Subsystem.h"

class Shooter : public Subsystem {
 public:
  void updateSubsystem() override;
  void initSubsystem() override;

 private:
  // output in range [-128, 127]
  void setConveyor(int output);
  // output in range [-128, 127]
  void setShooterWheels(int output);
  // output in range [-128, 127]
  void setRotationTurret(int output);
  // output in range [-128, 127]
  void setSlider(int output);

  void runConveyorFromInput();
  void rotateTurretFromInput();
  void runShooterWheelsFromInput();
  void runSliderFromInput();

  bool isShooterToggled;
  bool isButtonAlreadyPressed;
  int sliderAngle;
};