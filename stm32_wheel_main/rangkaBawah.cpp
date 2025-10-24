#include "rangkaBawah.h"
#include <cmath>

RangkaBawah::RangkaBawah(): motor1(0, 0), motor2(0,0), motor3(0,0) {}
RangkaBawah::RangkaBawah(
  int sel_1, int pwm_1,
  int sel_2, int pwm_2,
  int sel_3, int pwm_3
): motor1(sel_1, pwm_1), 
   motor2(sel_2, pwm_2), 
   motor3(sel_3, pwm_3)
{}

void RangkaBawah::moveRobot(float v_w1, float v_w2, float v_w3) {
  if(v_w1 > 0) {
    motor1.CW(static_cast<uint16_t>(fabs(v_w1)));
  } else if(v_w1 < 0) {
    motor1.CCW(static_cast<uint16_t>(fabs(v_w1)));
  } else {
    motor1.STOP();
  }

  if(v_w2 > 0) {
    motor2.CW(static_cast<uint16_t>(fabs(v_w2)));
  } else if(v_w2 < 0) {
    motor2.CCW(static_cast<uint16_t>(fabs(v_w2)));
  } else {
    motor2.STOP();
  }

  if(v_w3 > 0) {
    motor3.CW(static_cast<uint16_t>(fabs(v_w3)));
  } else if(v_w3 < 0) {
    motor3.CCW(static_cast<uint16_t>(fabs(v_w3)));
  } else {
    motor3.STOP();
  }
}