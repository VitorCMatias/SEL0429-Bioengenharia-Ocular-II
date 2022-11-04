
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <UnicViewAD.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

/*************************************************************
Indice das telas
*/

const int picIdIntro = 0;                      // PicId da tela de introdução              (PicId 00 - Intro    )
const int picIdSenha = 1;                      // PicId da tela de senha                 (PicId 01 - Audio    )
const int picIdTipo = 2;                       // PicId da tela do tipo evento                    (PicId 02 - RTC      )
const int picIdTeoria0 = 3;                    // PicId da tela Introdução teórica              (PicId 03 - CurveA0  )
const int picIdTeoria1 = 4;                    // PicId da tela Introdução teórica              (PicId 03 - CurveA0  )
const int picIdTeoria2 = 5;                    // PicId da tela Introdução teórica              (PicId 03 - CurveA0  )
const int picIdTeoria3 = 6;                    // PicId da tela Introdução teórica              (PicId 03 - CurveA0  )
const int picIdTeoria4 = 7;                    // PicId da tela Introdução teórica              (PicId 03 - CurveA0  )
const int picIdTeoria5 = 8;                    // PicId da tela Introdução teórica              (PicId 03 - CurveA0  )
const int picIdIdPassos0 = 9;                  // PicId da tela de passos para aplicação    (PicId 04 - CurveSim )
const int picIdIdPassos1 = 10;                 // PicId da tela de passos para aplicação    (PicId 04 - CurveSim )
const int picIdIdPassos2 = 11;                 // PicId da tela de passos para aplicação    (PicId 04 - CurveSim )
const int picIdIdPassos3 = 12;                 // PicId da tela de passos para aplicação    (PicId 04 - CurveSim )
const int picIdIdPassos4 = 13;                 // PicId da tela de passos para aplicação    (PicId 04 - CurveSim )
const int picIdArmacao = 14;                   // PicId da tela de escolha armação            (PicId 05 - Pressure )
const int picIdMaterial = 15;                  // PicId da tela de escolha material                  (PicId 06 - Led      )
const int picIdCor = 16;                       // PicId da tela de escolha cor                 (PicId 07 - Text     )
const int picIdLente = 17;                     // PicId da tela de escolha lente              (PicId 08 - Settings )
const int picIdHaste = 18;                     // PicId da tela de escolha haste               (PicId 09 - Volume   )
const int picIdAnalise = 19;                   // PicId da tela analise
const int picIdHorario = 20;                   // PicId da tela analise horario   
const int picIdCeu0 = 21;                      // PicId da tela escolha ceu 
const int picIdCeu1 = 22;                      // PicId da tela escolha ceu 
const int picIdCeu2 = 23;                      // PicId da tela escolha ceu 
const int picIdSup0 = 24;                      // PicId da tela escolha sup
const int picIdSup1 = 25;                      // PicId da tela escolha sup  
const int picIdDados = 26;                     // PicId da tela escolha confirmação .....Talvez não sei fazer
const int picIdResultado = 27;                 // PicId da tela escolha Resultado ....... Confirmar se vai ser assim msm a resposta

/*******************************************************************************************************************************************
 * Variáveis da tela de introdução (PicId 0 - intro)
 */

const int initDemo = 1000;                  // "Return Value" do único botão da tela de introdução (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela senha (PicId 1 - Senha)
 */

const int cont1 = 1001;                  // "Return Value" do botão da tela continuar
const int volt1 = 1002;                  // "Return Value" do botão da tela voltar

long senha;                            //variavel da senha


/*******************************************************************************************************************************************
 * Variáveis da tela de Tipo (PicId 2 - tipo)
 */
 
const int feira = 1000;                  // "Return Value" do botão feira
const int universidade = 1001;           // "Return Value" do botão universidade
const int cont2 = 1001;                  // "Return Value" do botão da tela continuar
const int volt2 = 1002;                  // "Return Value" do botão da tela voltar


/*******************************************************************************************************************************************
 * Variáveis da tela teoria 0 (PicId 3 - teoria)
 */

const int teoria0= 1000;                  // "Return Value" do único botão da tela  (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela de teoria 1 (PicId 4 - teoria)
 */

const int teoria1 = 1000;                  // "Return Value" do único botão da tela (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela de teoria 2 (PicId 5 - teoria)
 */

const int teoria2 = 1000;                  // "Return Value" do único botão da tela (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela de teoria 3 (PicId 6 - teoria)
 */

const int teoria3 = 1000;                  // "Return Value" do único botão da tela (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela de teoria 4 (PicId 7 - teoria)
 */

const int teoria4 = 1000;                  // "Return Value" do único botão da tela (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela de teoria 5 (PicId 8 - teoria)
 */

const int teoria5 = 1000;                  // "Return Value" do único botão da tela (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela passos 0 (PicId 9 - passos)
 */

const int cont9 = 1001;                  // "Return Value" do botão da tela continuar
const int volt9 = 1002;                  // "Return Value" do botão da tela voltar

/*******************************************************************************************************************************************
 * Variáveis da tela passos 1 (PicId 10 - passos)
 */

const int cont10 = 1001;                  // "Return Value" do botão da tela continuar
const int volt10 = 1002;                  // "Return Value" do botão da tela voltar

/*******************************************************************************************************************************************
 * Variáveis da tela passos 2 (PicId 11 - passos)
 */

const int cont11 = 1001;                  // "Return Value" do botão da tela continuar
const int volt11 = 1002;                  // "Return Value" do botão da tela voltar

/*******************************************************************************************************************************************
 * Variáveis da tela passos 3 (PicId 12 - passos)
 */

const int cont12 = 1001;                  // "Return Value" do botão da tela continuar
const int volt12 = 1002;                  // "Return Value" do botão da tela voltar

/*******************************************************************************************************************************************
 * Variáveis da tela passos 4 (PicId 13 - passos)
 */

const int cont13 = 1001;                  // "Return Value" do botão da tela continuar
const int volt13 = 1002;                  // "Return Value" do botão da tela voltar

/*******************************************************************************************************************************************
 * Variáveis da tela armacao (PicId 14 - Armação)
 */

const int cont14 = 1001;                  // "Return Value" do botão da tela continuar
const int arm_quarado = 1000;             // "Return Value" do botão da tela armacao quadrada
const int arm_arredondada = 1000;         // "Return Value" do botão da tela armacao arredondada
const int arm_mascara = 1000;             // "Return Value" do botão da tela armacao mascara
const int arm_redonda = 1000;             // "Return Value" do botão da tela armacao redonda

/*******************************************************************************************************************************************
 * Variáveis da tela material (PicId 15 - material)
 */

const int cont15 = 1001;                  // "Return Value" do botão da tela continuar
const int volt15 = 1002;                  // "Return Value" do botão da tela voltar
const int mat_plastico = 1000;            // "Return Value" do botão da tela 
const int mat_metal = 1000;               // "Return Value" do botão da tela 
const int mat_madeira = 1000;             // "Return Value" do botão da tela 
const int mat_outro = 1000;               // "Return Value" do botão da tela 

/*******************************************************************************************************************************************
 * Variáveis da tela lente (PicId 16 - cor )
 */

const int cont16 = 1001;                  // "Return Value" do botão da tela continuar
const int volt16 = 1002;                  // "Return Value" do botão da tela voltar
const int cor_marrom = 1000;            // "Return Value" do botão da tela 
const int cor_verde = 1000;               // "Return Value" do botão da tela 
const int cor_preto = 1000;             // "Return Value" do botão da tela 

/*******************************************************************************************************************************************
 * Variáveis da tela lente  (PicId 17 - lente)
 */

const int cont17 = 1001;                  // "Return Value" do botão da tela continuar
const int volt17 = 1002;                  // "Return Value" do botão da tela voltar

// Descobrir como fazer o deslize

/*******************************************************************************************************************************************
 * Variáveis da tela haste (PicId 18 - cor haste)
 */

const int cont18 = 1001;                  // "Return Value" do botão da tela continuar
const int volt18 = 1002;                  // "Return Value" do botão da tela voltar
const int hast_fina = 1000;               // "Return Value" do botão da tela 
const int hast_media = 1000;              // "Return Value" do botão da tela 
const int hast_larga = 1000;              // "Return Value" do botão da tela 

/*******************************************************************************************************************************************
 * Variáveis da tela analise (PicId 19 - analise)
 */

const int cont19 = 1001;                  // "Return Value" do botão da tela continuar
const int hoje = 1000;            // "Return Value" do botão da tela 
const int def = 1000;               // "Return Value" do botão da tela 

/*******************************************************************************************************************************************
 * Inicialização do LCM
 */

LCM Lcm(Serial);                           // Necessário a Inicialização do LCM com o nome de Lcm e como parâmetro a Serial que será ligado o Display

/*******************************************************************************************************************************************
 * Inicialização dos LcmVars
 */
LcmVar IntensidadeSup(); //colocar o vp
LcmVar IntensidadeInf(); //colocar o vp
LcmVar Sensor(); //colocar o vp
LcmVar Aplicacao(); //colocar o vp

/*******************************************************************************************************************************************
 * Inicialização das funções
 */

int ler_sensor();
void controlar_fita(uint8_t porta, int intensidade);
void logica();
void caso();
void controlar_intensidade();

void setup() {
  Serial.begin(9600);
  Lcm.begin();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  
  Wire.setClock(400000);
  attachInterrupt(digitalPinToInterrupt(2), inicio, LOW);
}

void loop() {
 
 if(uni == 1){

 }

}

void incio(){


}

void logica(){


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
  pwm.setPWM(porta, 0, 900+18*intensidade);
}

void caso(){

}

void controlar_intensidade(){

}
