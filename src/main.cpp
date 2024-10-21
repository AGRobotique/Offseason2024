#include <CrcLib.h>

int slider_angle = 127;
int stopper_angle = 127;
int sliderOutput;

// Memoire pour les toggles de la manette
bool roombaState = false;
bool shooterState = false;
bool isLPressed = false;
bool isRPressed = false;

void setup() {
    CrcLib::Initialize(); // À INCLURE SINON RIEN NE MARCHE

    // Déclaration des moteurs
    CrcLib::InitializePwmOutput(CRC_PWM_1); // Roues Gauche
    CrcLib::InitializePwmOutput(CRC_PWM_2, true); // Roues Droite
    CrcLib::InitializePwmOutput(CRC_PWM_3); // Conveyor
    CrcLib::InitializePwmOutput(CRC_PWM_4); // Roomba
    CrcLib::InitializePwmOutput(CRC_PWM_5); // Shooter
    CrcLib::InitializePwmOutput(CRC_PWM_6); // 360d Turret
    CrcLib::InitializePwmOutput(CRC_PWM_7); // Treuil
    CrcLib::InitializePwmOutput(CRC_PWM_8); // Multiplier Lift
    CrcLib::InitializePwmOutput(CRC_PWM_9, 500, 2500); // Angle Slider
    CrcLib::InitializePwmOutput(CRC_PWM_10, 500, 2500); // Ball Stopper
    
    Serial.begin(9600); // On start la console pour debug
}
void loop() {
    CrcLib::Update(); // À INCLURE SINON RIEN NE MARCHE
    if (CrcLib::IsCommValid()) { // À INCLURE SINON RIEN NE MARCHE
      // Movement
      CrcLib::MoveArcade(ANALOG::JOYSTICK2_Y, ANALOG::JOYSTICK2_X, CRC_PWM_1, CRC_PWM_2);
      
      // Roomba
      if(CrcLib::ReadDigitalChannel(BUTTON::R1)){ // When R1 pressed
        // Toggle shenanigans to change the value of roombaState
        if (!isRPressed) {
          isRPressed = true;
          if (!roombaState){
            roombaState = true;
          } else {
            roombaState = false;
          }
        }
      } else {
        isRPressed = false;
      }
      
      if(roombaState){
      CrcLib::SetPwmOutput(CRC_PWM_4, 125);
      } else {
      CrcLib::SetPwmOutput(CRC_PWM_4, 0);
      }

      // Conveyor
      if(CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP)==1){ // If ColorUp, spin in one direction
      CrcLib::SetPwmOutput(CRC_PWM_3, 125);
      } else if(CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN)==1){ // If ColorDown, spin in other direction
      CrcLib::SetPwmOutput(CRC_PWM_3, -125);
      } else { // Default state otherwise the motor will never stop
      CrcLib::SetPwmOutput(CRC_PWM_3, 0);
      }

      // Turret
      CrcLib::SetPwmOutput(CRC_PWM_6, (CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X) / 1.5)); // Divided the output of the joystick to have more control over the angle at a cost of max speed

      // Slider
      if (CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y) < -100 or CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y) > 100) { // I hate servos, don't ask me how this works. For that, Mathieu is your guy
        slider_angle += CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y) / 120;
      }
      if (slider_angle < -127) {
        slider_angle = -127;
      } else if (slider_angle > 127) {
        slider_angle = 127;
      }

      //Stopper
      CrcLib::SetPwmOutput(CRC_PWM_9, slider_angle);

      CrcLib::SetPwmOutput(
        CRC_PWM_10,
        CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R) > 100 ?
          68 :
          map(1000 * sin((float) millis() / (float) 150), -1000, 1000, -90, -10)
      ); // A guy way smarter than me did this. No clue how it works, only that it makes the stopper wiggle when the button is not pressed and here again IT'S A SERVO! Don't start me. pls.
      
      if (CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT) == 1) {
        stopper_angle += 5;
      } else if (CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT) == 1) {
        stopper_angle -= 5;
      }
      // Ensuring the values stay inbounds
      if (stopper_angle < -127) {
        stopper_angle = -127;
      } else if (stopper_angle > 127) {
        stopper_angle = 127;
      }

      // Treuil
      if(CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT)==1){
        CrcLib::SetPwmOutput(CRC_PWM_7, 125);
      } else if(CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT)==1){
        CrcLib::SetPwmOutput(CRC_PWM_7, -125);
      } else {
        CrcLib::SetPwmOutput(CRC_PWM_7, 0);
      }

      // Lift
      if(CrcLib::ReadDigitalChannel(BUTTON::ARROW_UP)==1){
        CrcLib::SetPwmOutput(CRC_PWM_8, 125);
      } else if(CrcLib::ReadDigitalChannel(BUTTON::ARROW_DOWN)==1){
        CrcLib::SetPwmOutput(CRC_PWM_8, -125);
      } else {
        CrcLib::SetPwmOutput(CRC_PWM_8, 0);
      }

      // Shooter
      if(CrcLib::ReadDigitalChannel(BUTTON::L1)){
        // Toggle shenanigans yet again
        if (!isLPressed) {
          isLPressed = true;
          if (!shooterState){
            shooterState = true;
          } else {
            shooterState = false;
          }
        }
      } else {
        isLPressed = false;
      }
      
      if(shooterState){
      CrcLib::SetPwmOutput(CRC_PWM_5, -125);
      } else {
      CrcLib::SetPwmOutput(CRC_PWM_5, 0);
      }
    }

    // DONE! Not that complicated right?
    
    /* 
    The rest of your looping code
    ...
    */
}
