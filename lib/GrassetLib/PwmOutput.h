#pragma once

#include "CrcLib.h"

class PwmOutput {
 public:
  /**
   * pinID: CRC-provided pinIDs, see docs
   * reverse: bool to reverse output
   * minPulseWidth: minimum pulse width of PWM output, in microseconds
   * maxPulseWidth: maximum pulse width of PWM output, in microseconds
   */
  PwmOutput(unsigned char pinID, bool reverse = false, int minPulseWidth = 1000,
            int maxPulseWidth = 2000)
      : pinID{pinID} {
    CrcLib::InitializePwmOutput(pinID, minPulseWidth, maxPulseWidth, reverse);
  }

  // output: desired output, in range [-128, 127]
  void setOutput(signed char output) { CrcLib::SetPwmOutput(pinID, output); }

 private:
  unsigned char pinID;
};