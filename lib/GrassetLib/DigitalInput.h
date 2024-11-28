#pragma once

#include "CrcLib.h"

class DigitalInput {
 public:
  // pinID: CRC-provided pinIDs, see docs
  DigitalInput(unsigned char pinID) : pinID{pinID} {
    CrcLib::SetDigitalPinMode(pinID, INPUT);
  }

  // Returns: HIGH (5V) or LOW (0V)
  unsigned char getInput() { return CrcLib::GetDigitalInput(pinID); }

  // Returns: true if 5V, false if 0V
  bool getBoolInput() { return getInput() == HIGH; }

 private:
  unsigned char pinID;
};