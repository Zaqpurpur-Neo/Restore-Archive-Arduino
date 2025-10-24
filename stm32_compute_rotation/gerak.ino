void stopWheel() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_IDLE);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_IDLE);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_IDLE);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_IDLE);
}

void runStraightFront() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_BACK);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_FRONT);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_FRONT);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_BACK);
}

void runStraightBack() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_FRONT);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_BACK);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_BACK);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_FRONT);
}

void runStraightLeft() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_BACK);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_BACK);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_FRONT);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_FRONT);
}

void runStraightRight() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_FRONT);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_FRONT);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_BACK);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_BACK);
}

void runDiagonalTopLeft() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_BACK);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_IDLE);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_FRONT);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_IDLE);
}

void runDiagonalBottomRight() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_FRONT);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_IDLE);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_BACK);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_IDLE);
}

void runDiagonalTopRight() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_IDLE);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_FRONT);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_IDLE);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_BACK);
}

void runDiagonalBottomLeft() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_IDLE);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_BACK);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_IDLE);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_FRONT);
}