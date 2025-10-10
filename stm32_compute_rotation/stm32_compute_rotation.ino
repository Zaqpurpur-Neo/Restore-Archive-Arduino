#define BAUD_RATE_STM32 96000
#define wheel_1_pwm PB8 // fr
#define wheel_1_dig PA2 // fr

#define wheel_2_pwm PB7 // fl
#define wheel_2_dig PA3 // fl

#define wheel_3_pwm PB6 // bl 
#define wheel_3_dig PA4 // bl

#define wheel_4_pwm PB9 // br
#define wheel_4_dig PA5 // br

typedef struct JoyAnalog {
	int16_t lx;
	int16_t ly;
	int16_t rx;
	int16_t ry;
} JoyAnalog;

enum Rotation {
  MODE_FRONT,
  MODE_BACK,
  MODE_IDLE
};

void useMode12() {
  analogWriteFrequency(20000);
  analogWriteResolution(12);
}

void setup() {
  Serial.begin(115200);
  while(!Serial);

  useMode12();
  setWheel(wheel_1_pwm, wheel_1_dig);
  setWheel(wheel_2_pwm, wheel_2_dig);
  setWheel(wheel_3_pwm, wheel_3_dig);
  setWheel(wheel_4_pwm, wheel_4_dig);

  Serial1.begin(BAUD_RATE_STM32);
}

void setWheel(int pwm, int digital) {
  pinMode(pwm, OUTPUT);
  pinMode(digital, OUTPUT);
}

void motorControl(int pwm, int digital, int speed, Rotation rotation) {
  switch(rotation) {
    case MODE_FRONT:
      digitalWrite(digital, HIGH);
      analogWrite(pwm, speed);
      break;
    case MODE_BACK:
      digitalWrite(digital, LOW);
      analogWrite(pwm, speed);
      break;
    default:
      digitalWrite(digital, LOW);
      analogWrite(pwm, 0);
  }
}

int MAX = 4095;
int speed = MAX/2;

void loop() {
  if (Serial1.available()) {
	  JoyAnalog analog;
	  Serial1.readBytes((char*)&analog, sizeof(analog));

	  Serial.print("[Analog]");
	  Serial.print(" LX: "); Serial.print(analog.lx);
	  Serial.print(" LY: "); Serial.print(analog.ly);
	  Serial.print(" RX: "); Serial.print(analog.rx);
	  Serial.print(" RY: "); Serial.println(analog.ry);
  }
}

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
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_IDLE);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_FRONT);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_IDLE);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_FRONT);
}

void runDiagonalBottomRight() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_IDLE);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_BACK);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_IDLE);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_BACK);
}

void runDiagonalTopRight() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_FRONT);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_IDLE);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_FRONT);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_IDLE);
}

void runDiagonalBottomLeft() {
  motorControl(wheel_1_pwm, wheel_1_dig, speed, MODE_BACK);
  motorControl(wheel_2_pwm, wheel_2_dig, speed, MODE_IDLE);
  motorControl(wheel_3_pwm, wheel_3_dig, speed, MODE_BACK);
  motorControl(wheel_4_pwm, wheel_4_dig, speed, MODE_IDLE);
}



