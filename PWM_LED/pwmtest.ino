
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <UnicViewAD.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
constexpr float duty_cycle_1 = 80.0;
constexpr float duty_cycle_2 = 20.0;

int ler_sensor();
void controlar_fita(uint8_t porta, int intensidade);
void set_fita();

void setup() {
set_fita();

}

void loop() {
  controlar_fita(14, duty_cycle_1);
  controlar_fita(15, duty_cycle_2);
}


int ler_sensor()
{
  return analogRead(A2);
}

void controlar_fita(uint8_t porta, int intensidade){
  pwm.setPWM(porta, 0, (intensidade/100.0)*4095);
}

void set_fita(){

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  

  Wire.setClock(400000);
}