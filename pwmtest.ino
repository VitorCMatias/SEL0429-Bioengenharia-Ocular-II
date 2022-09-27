
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
float pwm = 100.0;

void setup() {

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  

  Wire.setClock(400000);
}

void loop() {
  pwm.setPWM(0, 0, (pwm/100.0)*4095);
  
}
