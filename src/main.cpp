#include <CrcLib.h>

void setup() {
  CrcLib::Initialize();
  Serial.begin(2000000);
}

void loop() {
  CrcLib::Update();
  Serial.println();
  if (CrcLib::IsCommValid())
  {
    CrcLib::PrintControllerState();
  }
  else
  {
    Serial.print("No remote controller successfully communicates with the CrcDuino");
  }
}