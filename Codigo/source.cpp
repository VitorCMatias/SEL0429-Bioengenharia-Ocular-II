#include"header.hpp"
#include<Arduino.h>

int ler_sensor()
{
  int x1, x2, x3;
   x1 = analogRead(A2);
   x2 = analogRead(A3);
   
   if (x2>x1) 
   {
     x3 = x2/x1;
     return x3*x2;
   }
   else 
   {
     x3 = x1/x2;
     return x3*x1;
   }
   
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

