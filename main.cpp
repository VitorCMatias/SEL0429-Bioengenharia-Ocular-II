// #include <Arduino.h>
// #include <SPI.h>
// #include <SD.h>
// // #include"cartao_SD.hpp"
// const short int porta_SD = 10;



// /*
//   haste
//   material da haste
//   cor da lente
//   armação
//   cor da armação
//   ponte
// */

// //const short int porta_SD = 10;




// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);

//     if (!SD.begin(porta_SD))
//     {
//       Serial.println("Erro ao inicializar o cartão SD");
//       return;
//     }

//     bool existencia_arquivo = SD.exists("data4.txt");
//     File dataFile = SD.open("data4.txt", FILE_WRITE);
//     const char *cabecalho = "olá pessoal!";

//     if (!existencia_arquivo)
//     {
//         dataFile.println(cabecalho);
//         dataFile.println("dados");
//     }else{
//         dataFile.println("dados");
//     }


//     dataFile.close();





// }

// void loop() {


//   while (true)
//   {
//     /* code */
//   }

  
  
// }


/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {

  Serial.begin(9600);
  while (!Serial) {

  }


  Serial.print("Initializing SD card...");

 
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");

    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
 
  File dataFile = SD.open("datalog1.txt", FILE_WRITE);

  for(int i = 0; i < 10; i++){
    dataFile.print("teste");
    dataFile.println(i);
    
  }
  
  dataFile.close();
 
  Serial.println("salvo");


  while(1);
}











