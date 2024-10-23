#include "Robot.h"
Robot robot = Robot{};

void setup() { robot.initRobot(); }

void loop() { robot.updateRobot(); }
