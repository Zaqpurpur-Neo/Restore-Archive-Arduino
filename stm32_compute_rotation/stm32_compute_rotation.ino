#include <SerialTransfer.h>

#define BAUD_RATE_STM32 9600

#define wheel_1_pwm PB8 // fr
#define wheel_1_dig PA2 // fr

#define wheel_2_pwm PB7 // fl
#define wheel_2_dig PA3 // fl

#define wheel_3_pwm PB6 // bl 
#define wheel_3_dig PA4 // bl

#define wheel_4_pwm PB9 // br
#define wheel_4_dig PA5 // br

typedef enum ActionType {
	BTN_UP = 0,
	BTN_RIGHT,
	BTN_DOWN,
	BTN_LEFT,
	BTN_UNKNOWN
} ActionType;

typedef struct JoyAnalog {
	int16_t lx;
	int16_t ly;
	int16_t rx;
	int16_t ry;
} JoyAnalog;

typedef struct Action {
	ActionType action;
	JoyAnalog joyAnalog;
	bool sendStick;
} Action;

enum Rotation {
  MODE_FRONT,
  MODE_BACK,
  MODE_IDLE
};

SerialTransfer myTransfer;

void useMode12() {
  analogWriteFrequency(20000);
  analogWriteResolution(12);
}

int normalize(int value) {
	return map(value, 0, 225, -127, 127);
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial1.begin(BAUD_RATE_STM32);
  myTransfer.begin(Serial1);

  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, LOW);

  /*
  useMode12();
  setWheel(wheel_1_pwm, wheel_1_dig);
  setWheel(wheel_2_pwm, wheel_2_dig);
  setWheel(wheel_3_pwm, wheel_3_dig);
  setWheel(wheel_4_pwm, wheel_4_dig);
  */

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
Action analog;

void loop() {
  if (myTransfer.available()) {
	  myTransfer.rxObj(analog);

	  Serial.print("[Analog]");
	  Serial.print(" LX: "); Serial.print(analog.joyAnalog.lx);
	  Serial.print(" LY: "); Serial.print(analog.joyAnalog.ly);
	  Serial.print(" RX: "); Serial.print(analog.joyAnalog.rx);
	  Serial.print(" RY: "); Serial.println(analog.joyAnalog.ry);

	  digitalWrite(PC13, LOW);
      delay(100);
      digitalWrite(PC13, HIGH);
  }
  delay(100);
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



