#include <Arduino.h>
#include <SPI.h>
#include <SD.h>


/*
  haste
  material da haste
  cor da lente
  armação
  cor da armação
  ponte
*/

const short int porta_SD = 2;


void salvar_dados(String dados);


void setup() {
  // put your setup code here, to run once:


}

void loop() {
  
  
}


void salvar_dados(const char* dados){

  SD.begin(porta_SD);

  bool existencia_arquivo = SD.exists("data.txt");
  File dataFile = SD.open("data.txt", FILE_WRITE);
  const char* cabecalho = "olá pessoal!";

  if (!existencia_arquivo)
  {
    dataFile.println(cabecalho);
    dataFile.println(dados);
  }
  
  dataFile.write(dados);
  



  dataFile.close();
}