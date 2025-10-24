#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    int pwm_pin;
    int selector_pin;
  public:
    Motor(int SEL_PIN, int PWN_PIN);
    static void PWM(int freq = 20000, int res = 12);

    void CW(int PWM_VALUE);
    void CCW(int PWM_VALUE);
    void STOP();
};

#endif