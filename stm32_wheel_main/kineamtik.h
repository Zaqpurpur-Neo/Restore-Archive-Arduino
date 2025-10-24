#ifndef KINEMATIK_H
#define KINEMATIK_H

#include <math.h>

class Kinematik {
  private:
    float alpha, vx, vy;
  public:
    Kinematik();
    float inverseKinematik(float alpha, float vx, float vy) {
      return (-sin(alpha) * vx) + (cos(alpha) * vy);
    }
};

#endif