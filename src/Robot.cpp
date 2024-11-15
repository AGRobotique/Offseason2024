#include "Robot.h"

Robot::Robot() {
  // To add a subsystem, add an object to the array and change the constant
  subsystems = new Subsystem* [RobotConstants::kNumberOfSubsystems] {
    new Drivetrain(), new Intake(), new Lift(), new Shooter()
  };
}

void Robot::initRobot() {
  CrcLib::Initialize();
  Serial.begin(9600);  // Serial monitor for debug

  // Init all subsystems
  for (int i = 0; i < RobotConstants::kNumberOfSubsystems; i++) {
    subsystems[i]->initSubsystem();
  }
}

void Robot::updateRobot() {
  CrcLib::Update();
  if (CrcLib::IsCommValid()) {
    // Update all subsystems
    for (int i = 0; i < RobotConstants::kNumberOfSubsystems; i++) {
      subsystems[i]->updateSubsystem();
    }
  }
}

Robot::~Robot() {
  // Destroy pointers held inside the array
  for (int i = 0; i < RobotConstants::kNumberOfSubsystems; i++) {
    delete subsystems[i];
  }
  // Destroy the array
  delete[] subsystems;
}
