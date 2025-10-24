#ifndef RANGKA_BAWAH_H
#define RANGKA_BAWAH_H

#include <cstdint>
#include "motor.h"

using namespace std;

class RangkaBawah {
  private:
    Motor motor1;
    Motor motor2;
    Motor motor3;
  public:
    RangkaBawah();
    RangkaBawah(
      int sel_1, int pwm_1,
      int sel_2, int pwm_2,
      int sel_3, int pwm_3
    );

    void moveRobot(float v_w1, float v_w2, float v_w3);
};

#endif