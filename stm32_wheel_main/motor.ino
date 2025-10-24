#include "motor.h"

void Motor::PWM(int freq, int res) {
  analogWriteResolution(res);
  analogWriteFrequency(freq);
}

Motor::Motor(int SEL_PIN, int PWN_PIN) {
  this->pwm_pin = PWN_PIN;
  this->selector_pin = SEL_PIN;

  pinMode(this->pwm_pin, OUTPUT);
  pinMode(this->selector_pin, OUTPUT);
  analogWrite(this->pwm_pin, 0);
}

void Motor::CW(int PWM_VALUE) {
  digitalWrite(this->selector_pin, HIGH);
  analogWrite(this->pwm_pin, PWM_VALUE);
}

void Motor::CCW(int PWM_VALUE) {
  digitalWrite(this->selector_pin, LOW);
  analogWrite(this->pwm_pin, PWM_VALUE);
}

void Motor::STOP() {
  analogWrite(this->pwm_pin, 0);
}