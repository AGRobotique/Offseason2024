#pragma once

#include "CrcLib.h"

class DigitalOutput {
 public:
  // pinID: CRC-provided pinIDs, see docs
  DigitalOutput(unsigned char pinID) : pinID{pinID} {
    CrcLib::SetDigitalPinMode(pinID, OUTPUT);
  }

  // output: HIGH (5V) or LOW (0V)
  void setOutput(unsigned char output) {
    CrcLib::SetDigitalOutput(pinID, output);
  }

  // output: true for 5V, false for 0V
  void setBoolOutput(bool output) { setOutput(output ? HIGH : LOW); }

 private:
  unsigned char pinID;
};