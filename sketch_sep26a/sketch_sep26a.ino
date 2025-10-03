#define wheel_1_lpwm 1
#define wheel_1_rpwm 2

#define wheel_2_lpwm 3
#define wheel_2_rpwm 4

#define wheel_3_lpwm 5
#define wheel_3_rpwm 6

#define wheel_4_lpwm 7
#define wheel_4_rpwm 8

enum Rotation {
  MODE_FRONT,
  MODE_BACK,
  MODE_IDLE
}

void useMode12() {
  analogWriteFrequency(20000);
  analogWriteResolution(12);
}

void setup() {
  setWheel(wheel_1_lpwm, wheel_1_rpwm);
  setWheel(wheel_2_lpwm, wheel_2_rpwm);
  setWheel(wheel_3_lpwm, wheel_3_rpwm);
  setWheel(wheel_4_lpwm, wheel_4_rpwm);
}

void setWheel(uint32_t wheel_lpwm, uint32_t  wheel_rpwm) {
  pinMode(wheel_lpwm, OUTPUT);
  pinMode(wheel_rpwm, OUTPUT);
}

void motorControl(uint32_t pin_lpwm, uint32_t pin_rpwm, uint16_t speed, Rotation rotation) {
  switch(rotation) {
    case MODE_FRONT:
      analogWrite(pin_lpwm, speed);
      analogWrite(pin_rpwm, 0);
      break;
    case MODE_BACK:
      analogWrite(pin_lpwm, 0);
      analogWrite(pin_rpwm, speed);
      break;
    default:
      analogWrite(pin_lpwm, 0);
      analogWrite(pin_rpwm, 0);
  }
}

uin16_t MAX = 4095;
uin16_t speed = MAX/2;

void runStraightFront() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_FRONT);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_FRONT);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_FRONT);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_FRONT);
}

void runStraightBack() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_BACK);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_BACK);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_BACK);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_BACK);
}

void runStraightLeft() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_BACK);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_FRONT);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_FRONT);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_BACK);
}

void runStraightRight() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_FRONT);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_BACK);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_BACK);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_FRONT);
}

void runDiagonalTopLeft() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_IDLE);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_FRONT);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_IDLE);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_FRONT);
}

void runDiagonalBottomRight() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_IDLE);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_BACK);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_IDLE);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_BACK);
}

void runDiagonalTopRight() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_FRONT);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_IDLE);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_FRONT);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_IDLE);
}

void runDiagonalBottomLeft() {
  motorControl(wheel_1_lpwm, wheel_1_rpwm, speed, MODE_BACK);
  motorControl(wheel_2_lpwm, wheel_2_rpwm, speed, MODE_IDLE);
  motorControl(wheel_3_lpwm, wheel_3_rpwm, speed, MODE_BACK);
  motorControl(wheel_4_lpwm, wheel_4_rpwm, speed, MODE_IDLE);
}

void loop() {

}
