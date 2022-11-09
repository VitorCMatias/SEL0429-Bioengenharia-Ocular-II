#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <UnicViewAD.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

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

/*******************************************************************************************************************************************
 * Inicialização dos LcmVars
 */

LcmVar ExitIntroButton(0);                 // "LcmVar" do botão da tela de introdução (PicId 0 - Intro)

LcmVar NavigationButtons(1);               // "LcmVar" dos botões de navegação da tela principal (PicId 10 - main)

LcmVar PicIdIndicator(10);                 // "LcmVar" dos campos que indicam o PicId atual



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

/*******************************************************************************************************************************************
 * Inicialização do código
 */

void setup() {
  Serial.begin(9600);
  Lcm.begin();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  
  Wire.setClock(400000);
  //attachInterrupt(digitalPinToInterrupt(2), inicio, LOW);
}

void loop() {

  /*******************************************************************************************************************************************
     * Início do código da tela de introdução (PicId 0 - Intro)*/

	if (ExitIntroButton.available())		// Verifica se chegou algo no "LcmVar" "ExitIntroButton"
	{
		if (ExitIntroButton.getData() == initDemo)	// Verifica se o valor recebido pelo "LcmVar" "ExitIntroButton" é o "Return Value" do botão da tela de introdução (PicId 0 - Intro) - que irá atribuir os valores a todos os campos
		{
			Lcm.changePicId(picIdMain);                           // Muda a tela para a tela principal (PicId 1 - senha)
		}
	}
    /* Término do código da tela de introdução (PicId 0 - Intro)
     *******************************************************************************************************************************************/

 


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
