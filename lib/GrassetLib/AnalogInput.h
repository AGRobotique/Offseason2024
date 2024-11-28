#pragma once

#include "CrcLib.h"

class AnalogInput {
 public:
  // pinID: CRC-provided pinIDs, see docs
  AnalogInput(unsigned char pinID) : pinID{pinID} {}

  // Returns: number in range [0, 1023]
  unsigned int getInput() { return CrcLib::GetAnalogInput(pinID); }

 private:
  unsigned char pinID;
};