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

typedef struct Action {
	ActionType action;
	int16_t lx;
	int16_t ly;
	int16_t rx;
	int16_t ry;
	bool sendStick;
} Action;

enum Rotation {
  MODE_FRONT,
  MODE_BACK,
  MODE_IDLE
};

void useMode12() {
  analogWriteFrequency(20000);
  analogWriteResolution(12);
}

int normalize(long value) {
	return map(value, 0, 225, -127, 127);
}

int MAX_SPEED = 4095;
int MAP_VALUE = 127;
int speed = MAX_SPEED/2;
Action analog;

void setup() {
  Serial.begin(57600);
  while(!Serial);
  Serial1.begin(BAUD_RATE_STM32);

  pinMode(PC13, OUTPUT);

  useMode12();
  setWheel(wheel_1_pwm, wheel_1_dig);
  setWheel(wheel_2_pwm, wheel_2_dig);
  setWheel(wheel_3_pwm, wheel_3_dig);
  setWheel(wheel_4_pwm, wheel_4_dig);

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

void kinematikProto() {
  Serial.print("[Analog]");
  Serial.print(" LX: "); Serial.print(analog.lx);
  Serial.print(" LY: "); Serial.print(analog.ly);
  Serial.print(" RX: "); Serial.print(analog.rx);
  Serial.print(" RY: "); Serial.println(analog.ry);

  int x = normalize(analog.lx);
  int y = normalize(analog.ly);
  int rot = normalize(analog.rx);

  int wh1 = x + y + rot;
  int wh2 = x - y - rot;
  int wh3 = -x - y + rot;
  int wh4 = -x + y - rot;

  int speed1 = (wh1 * MAX_SPEED) / MAP_VALUE;
  int speed2 = (wh2 * MAX_SPEED) / MAP_VALUE;
  int speed3 = (wh3 * MAX_SPEED) / MAP_VALUE;
  int speed4 = (wh4 * MAX_SPEED) / MAP_VALUE;

  Rotation dir1 = (speed1 >= 0) ? MODE_FRONT : MODE_BACK;
  Rotation dir2 = (speed2 >= 0) ? MODE_FRONT : MODE_BACK;
  Rotation dir3 = (speed3 >= 0) ? MODE_FRONT : MODE_BACK;
  Rotation dir4 = (speed4 >= 0) ? MODE_FRONT : MODE_BACK;

  motorControl(wheel_1_pwm, wheel_1_dig, speed1, dir1);
  motorControl(wheel_2_pwm, wheel_2_dig, speed2, dir2);
  motorControl(wheel_3_pwm, wheel_3_dig, speed3, dir3);
  motorControl(wheel_4_pwm, wheel_4_dig, speed4, dir4); 
}


void loop() {
    Serial.println("OK");
    digitalWrite(PC13, LOW);
    runStraightFront();

    if(Serial1.available() > 0) {
      Serial1.readBytes((char*)&analog, sizeof(analog));

      switch(analog.action) {
        case BTN_UP:
          runStraightFront();
          break;
        case BTN_DOWN:
          runStraightBack();
          break;
        case BTN_LEFT:
          runStraightLeft();
          break;
        case BTN_RIGHT:
          runStraightRight();
          break;
      }
    }
}





