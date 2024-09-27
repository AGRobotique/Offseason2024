#include <CrcLib.h>

void setup() {
  CrcLib::Initialize();
}

void loop() {
  CrcLib::Update();
}