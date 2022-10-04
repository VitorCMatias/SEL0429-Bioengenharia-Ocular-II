
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
constexpr float duty_cycle = 80.0;

void setup() {

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  

  Wire.setClock(400000);

  
}

void loop() {
    //pwm.setPWM(15, 0, (duty_cycle/100.0)*4095);

  for(float i =0.0; i <100.0;++i){
    pwm.setPWM(15, 0, (i/100.0)*4095);
    delay(100);
  }
  
    for(float i =100.0; i >0.0;--i){
    pwm.setPWM(15, 0, (i/100.0)*4095);
    delay(100);
  }

}