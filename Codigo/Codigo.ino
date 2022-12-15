/* Nome: Claudia Stefen Andrade. (Nº USP: 10748563)
Rogerio Longuinho de Souza. (Nº USP: 11320895)
Roque André G. Louzada. (Nº USP: 10746602)
Rodrigo Kenji Yaly Aoki. (N°USP: 10788738)
Vitor da Costa Matias (N° USP 11892153)*/

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
const int picIdArmacao1 = 2;                      // PicId da tela de armacao    
const int picIdArmacao2 = 3;                      // PicId da tela de armacao               
const int picIdMaterialArm = 4;                   // PicId da tela do material armacao                  
const int picIdMaterialArm2 = 5;                   // PicId da tela do material armacao                  

const int picIdPonte = 9;                         // PicId da tela da ponte            
const int picIdMaterialPonte = 10;                 // PicId da tela do material da ponte          
const int picIdHaste = 6;                         // PicId da tela da haste            
const int picIdMaterialHaste = 7;                 // PicId da tela do material da haste  1
const int picIdMaterialHaste2 = 8;               // PicId da tela do material da haste  2  

const int picIdCor_lente = 11;
const int picIdCor_lente2 = 12;
const int picIdIntens_lente = 13;

const int picIdTipoAnalise = 20;                  // PicId da tela do tipo de analise            
const int picIdCeu1 = 14;                         // PicId da tela do ceu       
     
const int picIdIdSuperficie1 = 15;                // PicId da tela da superficie 

const int picIdIdResultado = 18;                  // PicId da tela do resultado 

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

LcmVar Armacao(102);     
LcmVar Material1_arm(104);
LcmVar Material2_arm(105);
LcmVar Ponte(109);
LcmVar Material_ponte(110);
LcmVar Haste(106);
LcmVar Material_haste1(107);
LcmVar Material_haste2(108);
LcmVar Cor_Lente(111);
LcmVar intensidade_lente(113);

LcmVar EscolhaCeu(114); 
LcmVar EscolhaSup(115); 

LcmVar ResultProtecao(118); 

/*******************************************************************************************************************************************
 * Inicialização das funções*/

int ler_sensor();
void controlar_intensidade(uint8_t porta, int intensidade);
int resultado_sensor(int referencia);
void caso();

/*******************************************************************************************************************************************
 * Inicialização do código*/

void setup() {
  Serial.begin(115200);
  Lcm.begin();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  
  Wire.setClock(400000);
}

void loop() {

delay(100);
int PicId = Lcm.readPicId(); // ler a tela que o display está no momento
Serial.println(' ');
//Serial.println(PicId);
//delay(100);

  if(PicId == 13)
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

  if(PicId == 16) 
  {
    Serial.println("hjj");
    caso(); // verifica qual foi o caso escolhido

    // Aciona os LEDs do céu
    for(int i = 0; i < 4; i++){
      controlar_intensidade(portas[i], (int)c);
    }

    // Aciona os LEDs da superfície 
    for(int i = 4; i < 8; i++){
      controlar_intensidade(portas[i],(int)s);
    }

    Ref =  ler_sensor();

  }


  if(PicId == 17)// 
  {
    
     // Intensidade total com oculos
    for(int i = 0; i < 8; i++){
      controlar_intensidade(portas[i], 100);
    }

    total = resultado_sensor(leitura_total); // faz a leitura com os oculos e realiza os cálculos 

        // Aciona os LEDs para o determinado caso, com óculos 
    for(int i = 0; i < 4; i++){
      controlar_intensidade(portas[i], (int)c);
    }

    for(int i = 4; i < 8; i++){
      controlar_intensidade(portas[i],(int)s);
    }

    situacao = resultado_sensor(Ref); // faz a leitura com os oculos e realiza os cálculos



  }


  if(PicId == 18) // mostra o resultado obtido
  {
    ResultProtecao.write(situacao);
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
  
  int leitura_ceu = EscolhaCeu.read();
  Serial.println(leitura_ceu);

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


