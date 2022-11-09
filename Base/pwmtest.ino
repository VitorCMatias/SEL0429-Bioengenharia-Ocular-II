
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//#include <UnicViewAD.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
constexpr float duty_cycle_1 = 80.0;
constexpr float duty_cycle_2 = 20.0;

int ler_sensor();
void controlar_fita(uint8_t porta, int intensidade);
void set_fita();

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
