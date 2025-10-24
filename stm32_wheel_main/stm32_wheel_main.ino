#define BAUD_RATE_STM32 9600
#define THRESHOLD 60

// motor1 supra
#define supra_1_pwm PB8 // fr
#define supra_1_sel PA2 // fr

// motor2 karisam
#define karisma_2_pwm PB7 // fl
#define karisma_2_sel PA3 // fl

// motor2 astrea
#define astrea_3_pwm PB6 // bl 
#define astrea_3_sel PA4 // bl

#include <math.h>

#include "kineamtik.h"
#include "motor.h" 
#include "rangkaBawah.h"

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

Motor motor1(supra_1_sel, supra_1_pwm);
Motor motor2(karisma_2_sel, karisma_2_pwm);
Motor motor3(astrea_3_sel, astrea_3_pwm);

double degree1 = 30 * PI/180;
double degree2 = 150 * PI/180;
double degree3 = 270 * PI/180;
int PWM = 3085;

float alpha, vx, vy, hipodesa;

float v1, v2, v3;

Action action;
Kinematik kinematik;
RangkaBawah rb;

int normalize(int16_t value) {
	return map(value, 0, 225, -127, 127);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(BAUD_RATE_STM32);
  Motor::PWM(20000, 12);
  rb = RangkaBawah(
    supra_1_sel, supra_1_pwm,
    karisma_2_sel, karisma_2_pwm,
    astrea_3_sel, astrea_3_pwm
  );
}

void loop() {
  // if(Serial1.available() > 0) {
    String data = Serial1.readStringUntil('\n');
    // Serial.println(data);
    sscanf(data.c_str(), "| %d | %d | %d | %d |", &action.lx, &action.ly, &action.rx, &action.ry);

    float LX = normalize(action.lx);
    float LY = normalize(action.ly);
    float RX = normalize(action.rx);

    if(RX < THRESHOLD && RX > -60) RX = 0;

    alpha = atan2(LY, LX);
    if(fabs(LX) < 60 && fabs(LY) < 60) {
      vx = 0;
      vy = 0;
    } else {
      vx = PWM * cos(alpha);  
      vy = PWM * sin(alpha) * -1;
    }

    // v1 = kinematik.inverseKinematik(alpha, vx, vy);
    // v2 = kinematik.inverseKinematik(alpha, vx, vy);
    // v3 = kinematik.inverseKinematik(alpha, vx, vy);

    v1 = kinematik.inverseKinematik(degree1, vx, vy);
    v2 = kinematik.inverseKinematik(degree2, vx, vy);
    v3 = kinematik.inverseKinematik(degree3, vx, vy);
    
    // Serial.printf("v1: %f, v2: %f, v3: %f\n", v1, v2, v3);
    
    rb.moveRobot(v1, v2, v3);

  // }
}
