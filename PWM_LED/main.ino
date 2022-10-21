
//#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>
//#include <UnicViewAD.h>

#include <header.hpp>



void setup() {
  Serial.begin(9600);
set_fita();

}

void loop() {
  controlar_fita(14, duty_cycle_1);
  controlar_fita(15, duty_cycle_2);
  Serial.println(ler_sensor());
  delay(100);

}


