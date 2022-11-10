#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <UnicViewAD.h>


/*************************************************************
Variaveis Gerais*/

const uint8_t portas[8] = {10,11,12,13,14,15,16,17};   //portas dos 8 quadrantes de intensidade (4 primeiras céu e 4 utltimas superficie);
int protecao_maxima;

/*************************************************************
Casos*/

float c;

struct casos{
  int memoria;
  float intensidade;
};

struct casos ceu[6] ={
                      {1000, 100},    // ceu limpo claro
                      {1000, 70},     // ceu limpo escuro
                      {1000, 90},     // ceu poucas nuvens claro
                      {1000, 70},     // ceu muitas nuves claro
                      {1000, 60},     // ceu chuvoso nuvens claras
                      {1000, 50}      // ceu chuvoso nunves escurar
                      };  

struct casos superficie[6] ={
                              {1000, 0.3*c},    // terra vermelha
                              {1000, 0.1*c},    // asfalto
                              {1000, 0.2*c},     // natureza
                              {1000, 0.4*c},     // agua
                              {1000, 0.9*c},     // neve
                              {1000, 0.15*c}      // cidade
                            };  




/*************************************************************
Indice das telas*/

const int picIdIntro = 0;                         // PicId da tela de introdução              (PicId 00 - Intro    )
const int picIdAramacao = 1;                      // PicId da tela de armacao               
const int picIdMaterialArm = 2;                   // PicId da tela do material armacao                  
const int picIdPonte = 3;                         // PicId da tela da ponte            
const int picIdMaterialPonte = 4;                 // PicId da tela do material da ponte          
const int picIdHaste = 5;                         // PicId da tela da haste            
const int picIdMaterialHaste = 6;                 // PicId da tela do material da haste          
const int picIdTipoAnalise = 7;                   // PicId da tela do tipo de analise            
const int picIdCeu = 8;                           // PicId da tela do ceu            
const int picIdIdSuperficie = 9;                  // PicId da tela da superficie 
const int picIdIdResultado = 10;                  // PicId da tela do resultado 

/*******************************************************************************************************************************************
 * Variáveis da tela de introdução (PicId 0 - intro)*/

const int initDemo = 1000;                  // "Return Value" do único botão da tela de introdução (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela senha (PicId 1 - Senha)*/

const int cont1 = 1001;                  // "Return Value" do botão da tela continuar
const int volt1 = 1002;                  // "Return Value" do botão da tela voltar

long senha;                            //variavel da senha

/*******************************************************************************************************************************************
 * Variáveis da tela de Tipo (PicId 2 - tipo)*/
 
const int feira = 1000;                  // "Return Value" do botão feira
const int universidade = 1001;           // "Return Value" do botão universidade
const int cont2 = 1001;                  // "Return Value" do botão da tela continuar
const int volt2 = 1002;                  // "Return Value" do botão da tela voltar


/*******************************************************************************************************************************************
 * Variáveis da tela teoria 0 (PicId 3 - teoria)*/

const int teoria0= 1000;                  // "Return Value" do único botão da tela  (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela de teoria 1 (PicId 4 - teoria)*/

const int teoria1 = 1000;                  // "Return Value" do único botão da tela (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela de teoria 2 (PicId 5 - teoria)*/

const int teoria2 = 1000;                  // "Return Value" do único botão da tela (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela material da haste (PicId 6 - mat haste)*/

const int  Hmaterial1 = 1000;                  // "Return Value" do botão 
const int  Hmaterial2 = 1000;                  // "Return Value" do botão
const int  Hmaterial3 = 1000;                  // "Return Value" do botão
const int  Hmaterial4 = 1000;                  // "Return Value" do botão

/*******************************************************************************************************************************************
 * Variáveis da tela do tipo de analise (PicId 7 - tipo analise)*/

const int agora = 1000;                  // "Return Value" do botão
const int escolha = 1000;                // "Return Value" do botão

/******************************************************************************************************************************************
 * Variáveis da tela céu (PicId 8 - céu)*/

const int ceu1 = 1000;                  // "Return Value" do botão 
const int ceu2 = 1000;                  // "Return Value" do botão 
const int ceu3 = 1000;                  // "Return Value" do botão
const int ceu4 = 1000;                  // "Return Value" do botão  
const int ceu5 = 1000;                  // "Return Value" do botão 
const int ceu6 = 1000;                  // "Return Value" do botão 

/*******************************************************************************************************************************************
 * Variáveis da tela superficie (PicId 9 - tipos superfície)*/

const int sup1 = 1001;                  // "Return Value" do botão 
const int sup2 = 1002;                  // "Return Value" do botão 
const int sup3 = 1002;                  // "Return Value" do botão 
const int sup4 = 1002;                  // "Return Value" do botão 
const int sup5 = 1002;                  // "Return Value" do botão 
const int sup6 = 1002;                  // "Return Value" do botão 


/*******************************************************************************************************************************************
 * Variáveis da tela passos 1 (PicId 10 - passos)*/

int total = 0;                  // valor da proteçao com luz total
int situacao = 0;               // valor da protecao para a situacao escolhida
char status;                    // status de proteção


/*******************************************************************************************************************************************
 * Inicialização do LCM*/

LCM Lcm(Serial);                           // Necessário a Inicialização do LCM com o nome de Lcm e como parâmetro a Serial que será ligado o Display

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

/*******************************************************************************************************************************************
 * Inicialização dos LcmVars*/


LcmVar IntensidadeSup(); //colocar o vp
LcmVar IntensidadeInf(); //colocar o vp
LcmVar Sensor(); //colocar o vp
LcmVar Aplicacao(); //colocar o vp

/*******************************************************************************************************************************************
 * Inicialização das funções*/

int ler_sensor();
void controlar_intensidade(uint8_t porta, int intensidade);
int resultado_sensor();
void caso();

/*******************************************************************************************************************************************
 * Inicialização do código*/

void setup() {
  Serial.begin(9600);
  Lcm.begin();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  
  Wire.setClock(400000);
}

void loop() {

  int PicId = Lcm.readPicId();

  if(PicId == 7){

    // Intensidade total
    for(int i = 0; i < 8; i++){
      controlar_intensidade(portas[i], 100);
    }

    protecao_maxima = resultado_sensor();

     for(int i = 0; i < 8; i++){
       controlar_intensidade(portas[i], 0);
    }
  }

  if(PicId == 10)
  {
    

  }
 

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

int resultado_sensor(){

int max = 870;
int protecao = 0;


return protecao;
}

void controlar_intensidade(uint8_t porta, int intensidade){
  pwm.setPWM(porta, 0, 900+18*intensidade);
}

void caso(){



}


