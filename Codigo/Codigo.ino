#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <UnicViewAD.h>


/*************************************************************
Variaveis Gerais*/

const uint8_t portas[8] = {10,11,12,13,14,15,16,17};   //portas dos 8 quadrantes de intensidade (4 primeiras céu e 4 utltimas superficie);

/*************************************************************
Casos*/

float c,s; //intensidades do céu e da superfície 

struct casos{
  int memoria;         // valor da memoria salvo
  float intensidade;   // valor da intensidade referente a esse
};

struct casos ceu[6] ={
                      {1, 100},    // ceu limpo claro
                      {2, 70},     // ceu limpo escuro
                      {3, 90},     // ceu poucas nuvens claro
                      {4, 70},     // ceu muitas nuves claro
                      {5, 60},     // ceu chuvoso nuvens claras
                      {6, 50}      // ceu chuvoso nunves escurar
                      };  

struct casos superficie[6] ={
                              {1, 0.3*c},    // terra vermelha
                              {2, 0.1*c},    // asfalto
                              {3, 0.2*c},    // natureza
                              {4, 0.4*c},    // agua
                              {5, 0.9*c},    // neve
                              {6, 0.15*c}    // cidade
                            };  


/*************************************************************
Indice das telas*/

const int picIdIntro = 0;                         // PicId da tela de introdução 
const int picIdArmacao1 = 3;                      // PicId da tela de armacao    
const int picIdArmacao2 = 4;                      // PicId da tela de armacao               
const int picIdMaterialArm = 5;                   // PicId da tela do material armacao                  
const int picIdPonte = 6;                         // PicId da tela da ponte            
const int picIdMaterialPonte = 7;                 // PicId da tela do material da ponte          
const int picIdHaste = 8;                         // PicId da tela da haste            
const int picIdMaterialHaste = 9;                 // PicId da tela do material da haste  1
const int picIdMaterialHaste2 = 10;               // PicId da tela do material da haste  2       
const int picIdTipoAnalise = 20;                  // PicId da tela do tipo de analise            
const int picIdCeu1 = 25;                         // PicId da tela do ceu       
const int picIdCeu2 = 26;                         // PicId da tela do ceu    
const int picIdCeu3 = 27;                         // PicId da tela do ceu       
const int picIdIdSuperficie1 = 28;                // PicId da tela da superficie 
const int picIdIdSuperficie2 = 29;                // PicId da tela da superficie 
const int picIdIdResultado = 31;                  // PicId da tela do resultado 

/*******************************************************************************************************************************************
/************ Variáveis da tela ARMAÇÕES ******/

short int tipo_armacao; // 1 a 6 return

/************ Variáveis da tela MATERIAIS ******/

short int tipo_material1_arm;      // 1 a 4
short int tipo_material2_arm;    // 1 a 4

/************ Variáveis da tela PONTE ******/

short int tipo_ponte ;      // 1 a 3
short int tipo_material_ponte;    // 1 a 4

/************ Variáveis da tela HASTE ******/

short int haste;   // 1 a 6
short int tipo_material1_haste;    // 1 a 4
short int tipo_material2_haste;    // 1 a 4

/************ Variáveis da tela Lente ******/

short int tipo_lente ;      // 1 a 3
short int cor_lente;    // 1 a 4

/************ Variáveis da tela Sensor ******/

int Ref;                   // referência do caso escolhido
int leitura_total;         // referência da leitura total

/*******************************************************************************************************************************************
 * Variáveis da tela resultado (PicId 10 - resultado)*/

int total = 0;                  // valor da proteçao com luz total
int situacao = 0;               // valor da protecao para a situacao escolhida
char status[20];                // status de proteção


/*******************************************************************************************************************************************
 * Inicialização do LCM*/

LCM Lcm(Serial);                           // Necessário a Inicialização do LCM com o nome de Lcm e como parâmetro a Serial que será ligado o Display

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

/*******************************************************************************************************************************************
 * Inicialização dos LcmVars - Objetos com  seus endereços de memória*/ 

LcmVar Armacao(10);     
LcmVar Material1_arm(21);
LcmVar Material2_arm(22);
LcmVar Ponte(30);
LcmVar Material_ponte(31);
LcmVar Haste(40);
LcmVar Material_haste1(41);
LcmVar Material_haste2(42);

LcmVar EscolhaCeu(80); 
LcmVar EscolhaSup(80); 

LcmVar ResultProtecao(59); 
LcmVar Maxima(60);
LcmString Resultado(61);

/*******************************************************************************************************************************************
 * Inicialização das funções*/

int ler_sensor();
void controlar_intensidade(uint8_t porta, int intensidade);
int resultado_sensor(int referencia);
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

  int PicId = Lcm.readPicId(); // ler a tela que o display está no momento

  if(PicId == 7)
  {
    // liga tudo em Intensidade total
    for(int i = 0; i < 8; i++){
      controlar_intensidade(portas[i], 100);
    }

    leitura_total = ler_sensor(); // ler o sensor em intesidade total sem o óculos 

   
    // desliga a esfera
    for(int i = 0; i < 8; i++){
       controlar_intensidade(portas[i], 0);
    }
  }

  if(PicId == 10) 
  {
    
    caso(); // verifica qual foi o caso escolhido

    // Aciona os LEDs do céu
    for(int i = 0; i < 4; i++){
      controlar_intensidade(portas[i], (int)c);
    }

    // Aciona os LEDs da superfície 
    for(int i = 4; i < 8; i++){
      controlar_intensidade(portas[i],(int)s);
    }

  }

  if(PicId == 11)
  {
      // Leitura sensor sem óculos do caso
     Ref =  ler_sensor();
  }

  if(PicId == 12)// 
  {
     // Intensidade total com oculos
    for(int i = 0; i < 8; i++){
      controlar_intensidade(portas[i], 100);
    }

    total = resultado_sensor(leitura_total); // faz a leitura com os oculos e realiza os cálculos 

  }

  if(PicId == 13)
  {
        // Aciona os LEDs para o determinado caso, com óculos 
    for(int i = 0; i < 4; i++){
      controlar_intensidade(portas[i], (int)c);
    }

    for(int i = 4; i < 8; i++){
      controlar_intensidade(portas[i],(int)s);
    }

    situacao = resultado_sensor(Ref); // faz a leitura com os oculos e realiza os cálculos 
  }


  if(PicId == 15) // mostra o resultado obtido
  {
    Maxima.write(total);
    ResultProtecao.write(situacao);

    if(situacao>70) status[20] ='protegido';
    else status[20] ='desprotegido'; 

    Resultado.write(status,20);
  }

  if(PicId == 0)
  {
    //desliga os leds quando vai para a tela inicial
      for(int i = 0; i < 8; i++)
      {
          controlar_intensidade(portas[i], 0);
      }
  }
 

}

// Funções 

int ler_sensor() // leitura dos sensores e realiza a razão 
{
  int x1, x2, x3;
   x1 = analogRead(A2);
   x2 = analogRead(A3);
   
   x3 = x1/x2;
  
  return x3; 
}

int resultado_sensor(int referencia) // analisa o resultado com o oculos
{

    int Ref2 = 0;                // referencia com o oculos
    int sensor_oculos = 0;       //  valor do sensor com o oculos
    int max = 0;                 // razão entre as duas referências
    float protecao = 0;          // resultado da proteção

    Ref2 = analogRead(A2);      
    max = Ref2/referencia;
    
    sensor_oculos = analogRead(A3);

    protecao = (int)(sensor_oculos/max)*100;

    return protecao;
}


void controlar_intensidade(uint8_t porta, int intensidade){
  pwm.setPWM(porta, 0, 900+18*intensidade);
}

void caso() // determina qual caso foi escolhido pelo usuário 
{
  
  int leitura_ceu = EscolhaCeu.getData();

    for(int j = 0; j<6;j++)
    {
      if(ceu[j].memoria == leitura_ceu){
         c = ceu[j].intensidade;
         break;
      }
    }
  
  int leitura_sup = EscolhaSup.getData();

    for(int j = 0; j<6;j++)
    {
      if(superficie[j].memoria == leitura_sup){
         s = superficie[j].intensidade;
         break;
      }
    }

}


