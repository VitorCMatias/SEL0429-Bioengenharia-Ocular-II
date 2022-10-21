#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
constexpr float duty_cycle_1 = 80.0;
constexpr float duty_cycle_2 = 20.0;

int ler_sensor();
void controlar_fita(uint8_t porta, int intensidade);
void set_fita();