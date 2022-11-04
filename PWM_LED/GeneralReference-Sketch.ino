/*
# Arquivo:

	Referencia_Geral.ino 

# Projeto:

	UnicView AD.ino - Exemplo Referência Geral

# Descrição:

	Essa demonstração exemplifica várias situações.
	As situações foram divididas em oito partes.
	Cada uma dessas partes é colocada em uma tela diferente.

	A demonstração inícia em uma tela com o Logo da Victor Vision,
	tocando nesse logo a tela muda para a tela principal.

	Nessa tela principal existe oito botões, cada botões levando para uma situação.

	* (PicId 1 - Audio    ) - Áudio

	É uma simulação de um player de música com seus controles.
	(Repeat) (Previous) (Play/Pause) (Next) (Stop) (Mute) (Volume)

	* (PicId 2 - RTC      ) - RTC

	Mostra e edita a data e hora do display.
	Podendo editar seus campos indidualmente clicando sobre o campo,
	ou usando um dos três botões que irá realizar alterações em sequência. 

	* (PicId 3 - CurveA0  ) - Curva A0

	Exibe um gráfico que é preenchido com os valores que são lidos pelo pino analógico A0.

	* (PicId 4 - CurveSim ) - Simulação da curva

	Exibe um gráfico que pode exibir dois exemplos de gráficos,
	um deles é uma ECG e o outro senóides, ou usando um knob para criar o gráfico manualmente.

	* (PicId 5 - Pressure ) - Pressão 

	Exibe um ponteiro que simula um controle de pressão,
	e tem duas meneiras de inserir o valor, um deles é por um slide na área inferior,
	o outro jeito é por um teclado numérico.

	* (PicId 6 - Led      ) - LED

	Exibe quatro controles(ON/OFF) de LEDs, podendo alterar seus estado individualmente,
	ou usando os botões superiores para ligar todos, desligar todos e mudar o estado de todos.

	* (PicId 7 - Text     ) - Texto

	Contêm dois campos, um de QR code e um de texto.
	O campo de QR code codifica o texto escrito no campo de texto.
	Quando o campo de texto é tocado, é exibido um teclado para digitar o texto,
	quando finalizado o texto é substituido pelo digitado, e logo a baixo é exibido o texto invertido

	* (PicId 8 - Settings ) - Ajustes 

	Essa tela possui vários campos de ajustes.
	(Backlight) (Buzzer) (Versão do firmware) (Reset) (Calibração) 

	 * Circuito

	 - 4 LEDs
	 - 4 resistores ( 330 Ohm )
	 - 1 potenciômetro ( 100k Ohm )

	 Os ânodos dos leds serão ligados nos pinos 4, 5, 6 e 7.
	 Um dos lados dos resistores serão ligados no catodo dos LEDs,
	 e o outro lado dos resistores ligado no terra ( GND ).
 
	 Pino 1 do potenciômetro ligado no terra.
	 Pino 2 do potenciômetro ligado no pino analógico A0.
	 Pino 3 do potenciômetro ligado no 5 volts.

# Documentação do projeto:

	http://www.victorvision.com.br/projects/arduino-system/library/site/examples/generalreference/

# Autores:

	* Andreo de Freitas
	* Rafael Moura (revisão)

# Licença:

	Copyright (c) 2020 Proculus Technologies Limited and Victor Vision LTDA

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

 */

#include <UnicViewAD.h>

/*******************************************************************************************************************************************
 * Índice das telas (Screens)
 */


/* 
 * Os valores atribuídos às constantes são os "PicIds".
 * Os "PicIds" são definidos no projeto do UnicView AD.
 */

const int picIdIntro = 0;                   // PicId da tela de introdução              (PicId 00 - Intro    )
const int picIdAudio = 1;                   // PicId da tela de áudio                   (PicId 01 - Audio    )
const int picIdRtc = 2;                     // PicId da tela do RTC                     (PicId 02 - RTC      )
const int picIdCurveA0 = 3;                 // PicId da tela de curva A0                (PicId 03 - CurveA0  )
const int picIdCurveSimulation = 4;         // PicId da tela de simulação da curva      (PicId 04 - CurveSim )
const int picIdPressure = 5;                // PicId da tela de pressão                 (PicId 05 - Pressure )
const int picIdLeds = 6;                    // PicId da tela de LED                     (PicId 06 - Led      )
const int picIdText = 7;                    // PicId da tela de texto                   (PicId 07 - Text     )
const int picIdSettings = 8;                // PicId da tela de ajustes                 (PicId 08 - Settings )
const int picIdVolume = 9;                  // PicId da tela de volume                  (PicId 09 - Volume   )
const int picIdMain = 10;                   // PicId da tela principal                  (PicId 10 - Main     )

/*******************************************************************************************************************************************
 * Variáveis da tela de introdução (PicId 0 - intro)
 */

const int initDemo = 1000;                  // "Return Value" do único botão da tela de introdução (A tela inteira é o botão)

/*******************************************************************************************************************************************
 * Variáveis da tela principal (PicId 10 - Main)
 */

const int navigateToAudio = 1;              // "Return Value" do botão de navegação para o áudio (PicId 1 - Audio)
const int navigateToRtc = 2;                // "Return Value" do botão de navegação para o RTC (PicId 2 - RTC)
const int navigateToCurveA0 = 3;            // "Return Value" do botão de navegação para o curva A0 (PicId 3 - CurveA0)
const int navigateToCurveSimulation = 4;    // "Return Value" do botão de navegação para o simulação de curvas (PicId 4 - CurveSim)
const int navigateToPressure = 5;           // "Return Value" do botão de navegação para o pressão (PicId 5 - Pressure)
const int navigateToLed = 6;                // "Return Value" do botão de navegação para o LED (PicId 6 - Led)
const int navigateToText = 7;               // "Return Value" do botão de navegação para o texto (PicId 7 - Text)
const int navigateToSettings = 8;           // "Return Value" do botão de navegação para o ajustes  (PicId 8 - Settings)

/*******************************************************************************************************************************************
 * Variáveis da tela de áudio (PicId 1 - Audio)
 */

const int navigateToVolume = 111;           // "Return Value" do botão de navegação para o volume (PicId 9 - Volume)
const int audioControlsMute = 110;          // "Return Value" do botão de controle da tela de áudio (PicId 1 - Audio) - Ativa / desativa Mudo
const int audioControlsRepeat = 120;        // "Return Value" do botão de controle da tela de áudio (PicId 1 - Audio) - Ativa / desativa repetir
const int audioControlsPrevious = 121;      // "Return Value" do botão de controle da tela de áudio (PicId 1 - Audio) - Áudio anterior
const int audioControlsPlayPause = 122;     // "Return Value" do botão de controle da tela de áudio (PicId 1 - Audio) - Play / pause
const int audioControlsNext = 123;          // "Return Value" do botão de controle da tela de áudio (PicId 1 - Audio) - Próximo áudio
const int audioControlsStop = 124;          // "Return Value" do botão de controle da tela de áudio (PicId 1 - Audio) - Para a reprodução

const int quantityOfTracks = 27;            // Quantidade de áudios
int currentTrack = 1;                       // Armazena o valor do áudio atual
bool isMuted = false;                       // Armazena a situação do controle mudo | ativado/desativado
bool isRepeating = false;                   // Armazena a situação do controle de repetição | ativado/desativado
bool previousDisabled = true;               // Armazena a situação do controle de retornar um áudio | habilitade/desabilitado
bool isPlaying = false;                     // Armazena a situação do controle de reprodução de áudio | play / pause
bool nextDisabled = false;                  // Armazena a situação do controle de avançar um áudio | habilitade/desabilitado
bool isStopped = true;                      // Armazena a situação do controle de parar  a reprodução de áudio
const int mutedVolume = 0;                  // valor enviado para o volume quando o áudio estão com o mudo ativo

/*******************************************************************************************************************************************
 * Variáveis da tela de RTC (PicId 2 - RTC)
 */

const int softwareControlCodeDay = 20;      // "Software Control Code" do "Numeric Input" que altera o valor do dia
const int softwareControlCodeMonth = 21;    // "Software Control Code" do "Numeric Input" que altera o valor do mês
const int softwareControlCodeYear = 22;     // "Software Control Code" do "Numeric Input" que altera o valor do ano
const int softwareControlCodeHour = 23;     // "Software Control Code" do "Numeric Input" que altera o valor da hora
const int softwareControlCodeMinute = 24;   // "Software Control Code" do "Numeric Input" que altera o valor do minuto
const int softwareControlCodeSecond = 25;   // "Software Control Code" do "Numeric Input" que altera o valor do segundo

const int rtcSelectedIconNone = 0;          // Valor usado para desativar o efeito de seleção do RTC
const int rtcSelectedIconDay = 1;           // Valor usado para ativar o efeito de seleção do campo dia
const int rtcSelectedIconMonth = 2;         // Valor usado para ativar o efeito de seleção do campo mês
const int rtcSelectedIconYear = 3;          // Valor usado para ativar o efeito de seleção do campo ano
const int rtcSelectedIconHour = 4;          // Valor usado para ativar o efeito de seleção do campo hora
const int rtcSelectedIconMinute = 5;        // Valor usado para ativar o efeito de seleção do campo minuto
const int rtcSelectedIconSecond = 6;        // Valor usado para ativar o efeito de seleção do campo segundo

const int rtcButtonDay = 240;               // "Return Value" do botão para alterar o valor do dia
const int rtcButtonMonth = 241;             // "Return Value" do botão para alterar o valor do mês
const int rtcButtonYear = 242;              // "Return Value" do botão para alterar o valor do ano
const int rtcButtonHour = 243;              // "Return Value" do botão para alterar o valor do hora
const int rtcButtonMinute = 244;            // "Return Value" do botão para alterar o valor do minuto
const int rtcButtonSecond = 245;            // "Return Value" do botão para alterar o valor do segundo
const int rtcButtonDate = 246;              // "Return Value" do botão para alterar os valores da data | dia / mês / ano
const int rtcButtonTime = 247;              // "Return Value" do botão para alterar os valores da hora | hora / minuto / segundo

bool keyboardIsOpen = false;                        // Armazena a situação do teclado do RTC | aberto / fechado
long int lastKeyboardResponseTime = 0;              // Armazena um valor de tempo usado para dar um espaço de tempo entre as verificações do teclado
const int keyboardIsOpenReadIntervalInMs = 1000;    // Espaço de tempo (em milissegundos) entre as verificações de teclado

int lastRtcDay;                             // Armazena o último valor configurado para o dia
int lastRtcMonth;                           // Armazena o último valor configurado para o mês
int lastRtcYear;                            // Armazena o último valor configurado para o ano
int lastRtcHour;                            // Armazena o último valor configurado para a hora
int lastRtcMinute;                          // Armazena o último valor configurado para o minuto
int lastRtcSecond;                          // Armazena o último valor configurado para o segundo

int currentRtcKeyboard = 0;                 // Armazena o valor atual de qual campo do RTC está sendo alterado

const int rtcKeyboardSequenceNone = 0;      // Valor atual do índice sequêncial para quando for atribuir mais de um valor no RTC - Sem sequência
const int rtcKeyboardSequenceDay = 1;       // Valor atual do índice sequêncial para quando for atribuir mais de um valor no RTC - Dia
const int rtcKeyboardSequenceMonth = 2;     // Valor atual do índice sequêncial para quando for atribuir mais de um valor no RTC - Mês
const int rtcKeyboardSequenceYear = 3;      // Valor atual do índice sequêncial para quando for atribuir mais de um valor no RTC - Ano
const int rtcKeyboardSequenceHour = 4;      // Valor atual do índice sequêncial para quando for atribuir mais de um valor no RTC - Hora
const int rtcKeyboardSequenceMinute = 5;    // Valor atual do índice sequêncial para quando for atribuir mais de um valor no RTC - minuto
const int rtcKeyboardSequenceSecond = 6;    // Valor atual do índice sequêncial para quando for atribuir mais de um valor no RTC - Segundo

/*******************************************************************************************************************************************
 * Variáveis da tela de curva A0 (PicId 3 - CurveA0)
 */

const int curveA0ControlPlay = 300;         // "Return Value" do botão de controle da tela de curva A0 (PicId 3 - CurveA0) - Inicia a leitura analógica do pino A0
const int curveA0ControlPause = 301;        // "Return Value" do botão de controle da tela de curva A0 (PicId 3 - CurveA0) - Pausa a leitura analógica do pino A0
const int curveA0ControlStop = 302;         // "Return Value" do botão de controle da tela de curva A0 (PicId 3 - CurveA0) - Para a leitura analógica do pino A0 e apaga todos os pontos lidos

bool curveA0isPlotting = false;             // Armazena se estão sendo realizado a leitura analógica do pino A0
const int curveA0AnalogPin = A0;            // Define qual pino amalógico será lido
long int lastCurveA0WriteTime = 0;          // Armazena um valor de tempo usado para dar um espaço de tempo entre as leituras do pino analógico
const int curveA0WriteIntervalInMs = 100;   // Espaço de tempo entre as leituras do pino analógico

/*******************************************************************************************************************************************
 * Variáveis da tela de simulação da curva (PicId 4 - CurveSim)
 */

const int curveSimulationSampleEcg = 410;   // "Return Value" do botão de controle da tela de simulação da curva (PicId 4 - CurveSim) - envia um exemplo de ECG
const int curveSimulationSampleSine = 411;  // "Return Value" do botão de controle da tela de simulação da curva (PicId 4 - CurveSim) - envia um exemplo de senoide

const int ecgSamplePoints[] = {             // Vetor com o exemplo de um traçado de ECG
  39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 41, 44, 47, 50, 52, 52, 48, 43, 41, 39, 39, 39, 37, 33, 38,
  45, 60, 75, 90, 100, 94, 80, 63, 46, 29, 17, 11, 17, 27, 34, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39
};

const int ecgSamplePointsLength = 55;       // Quantidade de pontos no exemplo de ECG
const int curveNumberOfPoints = 216;        // Quantidade máxima de pontos do gráfico da tela de simulação e curva (PicId 4 - CurveSim)

/*******************************************************************************************************************************************
 * Variáveis da tela de pressão (PicId 5 - Pressure)
 */

const int pressureAlertLevel = 90;          // Valor da pressão que será ativado o icone de alerta
int pressureSetpointValue = 0;              // Variável que receberá o novo valor de pressão
int currentPressureValue = 50;              // Variável de controle da pressão atual
bool adjustPressure = false;                // Variável que armazena a situação se a pressão precisa ser ajustada
long int lastPressureWriteTime = 0;         // Armazena um valor de tempo usado para dar um espaço de tempo entre as Atualizações do valor da pressão
const int pressureWriteIntervalInMs = 100;  // Espaço de tempo entre os ajustes de pressão

/*******************************************************************************************************************************************
 * Variáveis da tela de LED (PicId 6 - Led)
 */

const int ledControlsToggleLed1 = 611;          // "Return Value" do botão de controle da tela de LED (PicId 6 - Led) - Altera o estado do led 1 liga/desliga
const int ledControlsToggleLed2 = 612;          // "Return Value" do botão de controle da tela de LED (PicId 6 - Led) - Altera o estado do led 2 liga/desliga
const int ledControlsToggleLed3 = 613;          // "Return Value" do botão de controle da tela de LED (PicId 6 - Led) - Altera o estado do led 3 liga/desliga
const int ledControlsToggleLed4 = 614;          // "Return Value" do botão de controle da tela de LED (PicId 6 - Led) - Altera o estado do led 4 liga/desliga
const int ledControlsSetAllLedsToLow = 615;     // "Return Value" do botão de controle da tela de LED (PicId 6 - Led) - Desliga todos os leds
const int ledControlsToggleAllLeds = 616;       // "Return Value" do botão de controle da tela de LED (PicId 6 - Led) - Altera o estado de todos os leds liga/desliga
const int ledControlsSetAllLedsToHigh = 617;    // "Return Value" do botão de controle da tela de LED (PicId 6 - Led) - liga todos os leds

const int ledPin1 = 4;                      // Definição do pino que será ligado o led 1
const int ledPin2 = 5;                      // Definição do pino que será ligado o led 2
const int ledPin3 = 6;                      // Definição do pino que será ligado o led 3
const int ledPin4 = 7;                      // Definição do pino que será ligado o led 4

/*******************************************************************************************************************************************
 * Variáveis da tela de texto (PicId 7 - Text)
 */

const int textLengthInChars = 12;           // Tamanho da caixa de texto da tela de texto (PicId 7 - Text) em caracteres.

/*******************************************************************************************************************************************
 * Variáveis da tela de ajustes (PicId 8 - Settings)
 */

const int popupCancel = 240;                // "Return Value" do botão de controle da tela de ajustes   (PicId 8 - Settings) - Popup - CANCELAR
const int popupConfirm = 241;               // "Return Value" do botão de controle da tela de ajustes   (PicId 8 - Settings) - Popup - CONFIRMAR

/*******************************************************************************************************************************************
 * Variáveis da tela de volume(PicId 9 - Volume)
 */

int volume = 7;                             // Armazena o volume de reprodução do áudio
const int navigateFromVolume = 9;           // "Return Value" do botão de navegação voltando da tela de volume (PicId 9 - Volume)

/*******************************************************************************************************************************************
 * Inicialização do LCM
 */

LCM Lcm(Serial);                           // Necessário a Inicialização do LCM com o nome de Lcm e como parâmetro a Serial que será ligado o Display

/*******************************************************************************************************************************************
 * Inicialização dos LcmVars
 */

LcmVar ExitIntroButton(0);                 // "LcmVar" do botão da tela de introdução (PicId 0 - Intro)

LcmVar NavigationButtons(1);               // "LcmVar" dos botões de navegação da tela principal (PicId 10 - main)

LcmVar PicIdIndicator(10);                 // "LcmVar" dos campos que indicam o PicId atual

LcmVar AudioControls(100);                 // "LcmVar" dos botões de controle da tela de áudio (PicId 1 - Audio)
LcmVar AudioVolume(900);                   // "LcmVar" do controle de volume da tela de volume (PicId 9 - Volume)

LcmVar AudioRepeatIndicator(101);          // "LcmVar" do ícone que indica se os áudio estão para repetir
LcmVar AudioPreviousIndicator(102);        // "LcmVar" do ícone que indica se é possível voltar um áudio
LcmVar AudioPlayPauseIndicator(103);       // "LcmVar" do ícone que indica se quando pressionar o play/pause, irá iniciar ou pausar a reprodução
LcmVar AudioNextIndicator(104);            // "LcmVar" do ícone que indica se é possível avançar um áudio
LcmVar AudioStopIndicator(105);            // "LcmVar" do ícone que indica a possibilidade de parar a reprodução do áudio

LcmVar AudioCurrentTrackIndicator(110);    // "LcmVar" que mostra o áudio que está selecionado
LcmVar AudioLastTrackIndicator(111);       // "LcmVar" que mostra o último áudio possivel de ser selecionado

LcmVar RtcButtons(201);                    // "LcmVar" dos botões de controle que definem o RTC
LcmVar RtcSelectedIcons(200);              // "LcmVar" dos icones que podem ser selecionados para alteração

LcmVar KeyboardDay(210);                   // "LcmVar" do teclado que altera o valor do Dia
LcmVar KeyboardMonth(211);                 // "LcmVar" do teclado que altera o valor do Mês
LcmVar KeyboardYear(212);                  // "LcmVar" do teclado que altera o valor do Ano
LcmVar KeyboardHour(213);                  // "LcmVar" do teclado que altera o valor da Hora
LcmVar KeyboardMinute(214);                // "LcmVar" do teclado que altera o valor do Minuto
LcmVar KeyboardSecond(215);                // "LcmVar" do teclado que altera o valor do Segundo

LcmVar CurveA0Controls(301);               // "LcmVar" dos botões de controle da tela curva A0 (PicId 3 - CurveA0)
LcmVar CurveA0TemperatureIndicator(300);   // "LcmVar" dos icones que mostram a temperatura no termômetro da tela de curva A0 (PicId 3 - CurveA0)

LcmVar CurveSimulationSampleButtons(400);          // "LcmVar" dos exemplos de curvas da tela de simulação da curva (PicId 4 - CurveSim)
LcmVar CurveSimulationManualInput(410);            // "LcmVar" do Knob de controle de temperatura da tela de simulação da curva (PicId 4 - CurveSim)
LcmVar CurveSimulationTemperatureIndicator(420);   // "LcmVar" dos ícones que mostram a temperatura no termômetro da tela de simulação da curva (PicId 4 - CurveSim)

LcmVar PressureSetpoint(500);              // "LcmVar" da pressão configurada
LcmVar CurrentPressureIndicator(501);      // "LcmVar" do ícone de ponteiro central da pressão
LcmVar PressureAlertIndicator(502);        // "LcmVar" do ícone de alerta de alta pressão

LcmVar LedControls(600);                   // "LcmVar" dos controles de LED da tela de LED (PicId 6 - Led)
LcmVar Led1Indicator(601);                 // "LcmVar" do ícone que indica se o LED 1 está ligado
LcmVar Led2Indicator(602);                 // "LcmVar" do ícone que indica se o LED 2 está ligado
LcmVar Led3Indicator(603);                 // "LcmVar" do ícone que indica se o LED 3 está ligado
LcmVar Led4Indicator(604);                 // "LcmVar" do ícone que indica se o LED 4 está ligado

LcmString TextInput(700, textLengthInChars);    // "LcmString" da entrada de texto da tela de texto (PicId 7 - Text)
LcmString InvertedText(720, textLengthInChars); // "LcmString" do campo de texto invertido da tela de texto (PicId 7 - Text)

LcmVar BackLight(800);                     // "LcmVar" da entrada de configuração do backlight do display
LcmVar ReadVersionButton(801);             // "LcmVar" do botão de leitura da versão do firmware do display
LcmVar VersionIndicator(810);              // "LcmVar" do campo de texto que mostra a versão do firmware do display
LcmVar ActivateBuzzerButton(802);          // "LcmVar" do botão que toca o buzzer
LcmVar BuzzerActivationTime(803);          // "LcmVar" do valor de configuração do tempo de toque do buzzer
LcmVar CalibrateButton(804);               // "LcmVar" do botão de calibração
LcmVar ResetButton(805);                   // "LcmVar" do botão de resetar o display

/*******************************************************************************************************************************************
 * A função setup executa apenas uma única vez quando é iníciado
 */

void setup()
{
	Lcm.begin();            // Inicialização e configuração do lcm
  Serial.begin(115200);

	pinMode(ledPin1, OUTPUT);             // Configuração do pino do led 1
	pinMode(ledPin2, OUTPUT);             // Configuração do pino do led 2
	pinMode(ledPin3, OUTPUT);             // Configuração do pino do led 3
	pinMode(ledPin4, OUTPUT);             // Configuração do pino do led 4
}

/*******************************************************************************************************************************************
 * A função loop executa indefinidamente
 */

void loop()
{

    /*******************************************************************************************************************************************
     * Início do código da tela de introdução (PicId 0 - Intro)
     */

	if (ExitIntroButton.available())		// Verifica se chegou algo no "LcmVar" "ExitIntroButton"
	{
		if (ExitIntroButton.getData() == initDemo)	// Verifica se o valor recebido pelo "LcmVar" "ExitIntroButton" é o "Return Value" do botão da tela de introdução (PicId 0 - Intro) - que irá atribuir os valores a todos os campos
		{
			Lcm.changePicId(picIdMain);                           // Muda a tela para a tela principal (PicId 10 - main)
			
			AudioRepeatIndicator.write(isRepeating);            // Escreve no "LcmVar" "AudioRepeatIndicator" o valor da variável "isRepeating"
			AudioPreviousIndicator.write(previousDisabled);     // Escreve no "LcmVar" "AudioPreviousIndicator" o valor da variável "previousDisabled"
			AudioPlayPauseIndicator.write(isPlaying);           // Escreve no "LcmVar" "AudioPlayPauseIndicator" o valor da variável "isPlaying"
			AudioNextIndicator.write(nextDisabled);             // Escreve no "LcmVar" "AudioNextIndicator" o valor da variável "nextDisabled"
			AudioStopIndicator.write(isStopped);                // Escreve no "LcmVar" "AudioStopIndicator" o valor da variável "isStopped"
			AudioVolume.write(volume);                          // Escreve no "LcmVar" "AudioVolume" o valor da variável "volume"
			AudioLastTrackIndicator.write(quantityOfTracks);    // Escreve no "LcmVar" "AudioLastTrackIndicator" o valor da variável "quantityOfTracks"
			AudioCurrentTrackIndicator.write(currentTrack);     // Escreve no "LcmVar" "AudioCurrentTrackIndicator" o valor da variável "currentTrack"
			PressureAlertIndicator.write(0);                    // Escreve no "LcmVar" "PressureAlertIndicator" o valor "0"
		}
	}

    /*
     * Término do código da tela de introdução (PicId 0 - Intro)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela principal (PicId 10 - main)
     */

	if (NavigationButtons.available())                          // Verifica se chegou algo no "LcmVar" "NavigationButtons"
	{
		int value = NavigationButtons.getData();                // Atribui o valor recebido a variável "value"

		switch (value)                                          // Verifica qual dos "Return Values" dos botões de navegação que foi atribuido a variável "value"
		{
		case navigateToAudio:                                   // Caso o valor da variável "value" seja o "Return Value" "navigateToAudio"
		case navigateToRtc:                                     // Caso o valor da variável "value" seja o "Return Value" "navigateToRtc"
		case navigateToCurveA0:                                 // Caso o valor da variável "value" seja o "Return Value" "navigateToCurveA0"
		case navigateToCurveSimulation:                         // Caso o valor da variável "value" seja o "Return Value" "navigateToCurveSimulation"
		case navigateToPressure:                                // Caso o valor da variável "value" seja o "Return Value" "navigateToPressure"
		case navigateToLed:                                     // Caso o valor da variável "value" seja o "Return Value" "navigateToLed"
		case navigateToText:                                    // Caso o valor da variável "value" seja o "Return Value" "navigateToText"
		case navigateToSettings:                                // Caso o valor da variável "value" seja o "Return Value" "navigateToSettings"
		case navigateFromVolume:                                // Caso o valor da variável "value" seja o "Return Value" "navigateFromVolume"
		{
			const int picId = Lcm.readPicId();                  // Verifica qual o PicId atual e atribui a variável "picId"
			PicIdIndicator.write(picId);                        // Escreve no "LcmVar" "PicIdIndicator" o valor da variável "picId"
		}
		break;

		case navigateToVolume:                                  // Caso o valor da variável "value" seja o "Return Value" "navigateToVolume"
			if (isMuted == false)                               // Verifica se o mudo não foi ativado
			{
				Lcm.changePicId(picIdVolume);                   // Altera a tela para a tela de volume (PicId 9 - Volume)
				const int picId = Lcm.readPicId();              // Verifica qual o PicId atual e atribui a variável "picId"
				PicIdIndicator.write(picId);                    // Escreve no "LcmVar" "PicIdIndicator" o valor da variável "picId"
			}
			break;

		default:
			break;
		}
	}

    /*
     * Término do código da tela principal (PicId 10 - main)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de áudio (PicId 1 - Audio)
     */

    if (AudioControls.available())                              // Verifica se chegou algo no "LcmVar" "AudioControls"
    {
        int value = AudioControls.getData();                    // Atribui o valor recebido a variável "value"

        switch (value)                                          // Verifica qual dos "Return Values" dos botões de controle do áudio que foi atribuido a variável "value"
        {
        case audioControlsMute:                                 // Caso o valor da variável "value" seja o "Return Value" "audioControlsMute"
            if (isMuted == true)                                // Verifica se a variável "isMuted" é verdadeira
            {
                isMuted = false;                                // A variável "inMuted" se torna falso
                AudioVolume.write(volume);                      // Escreve no "LcmVar" "AudioVolume" o valor da variável "volume"
            }
            else
            {
                isMuted = true;                                 // A variável "inMuted" se torna verdadeira
                AudioVolume.write(mutedVolume);                 // Escreve no "LcmVar" "AudioVolume" o valor da variável "mutedVolume"
            }
            break;

        case audioControlsRepeat:                               // Caso o valor da variável "value" seja o "Return Value" "audioControlsRepeat"
            previousDisabled = false;                           // A variável "previousDisabled" se torna falso
            nextDisabled = false;                               // A variável "nextDisabled" se torna falso
            if (isRepeating == false)                           // Verifica se a variável "isRepeating" é falsa
            {
                isRepeating = true;                             // A variável "isRepeating" se torna verdadeira
            }
            else
            {
                isRepeating = false;                            // A variável "isRepeating" se torna falso
                if (currentTrack == quantityOfTracks)           // Verifica se a variável "currentTrack" é igual a "quantityOfTracks"
                {
                    nextDisabled = true;                        // A variável "nextDisabled" se torna verdadeira
                }
                else if (currentTrack == 1)                     // Verifica se a variável "currentTrack" é igual a 1
                {
                    previousDisabled = true;                    // A variável "previousDisabled" se torna verdadeira
                }
            }
            AudioRepeatIndicator.write(isRepeating);            // Escreve no "LcmVar" "AudioRepeatIndicator" o valor da variável "isRepeating"
            AudioPreviousIndicator.write(previousDisabled);     // Escreve no "LcmVar" "AudioPreviousIndicator" o valor da variável "previousDisabled"
            AudioNextIndicator.write(nextDisabled);             // Escreve no "LcmVar" "AudioNextIndicator" o valor da variável "nextDisabled"
            break;

        case audioControlsPrevious:                             // Caso o valor da variável "value" seja o "Return Value" "audioControlsPrevious"
            if (previousDisabled == false)                      // Verifica se a variável "previousDisabled" é falsa
            {
                currentTrack--;                                 // Decrementa 1 da variável "currentTrack"
                if (isRepeating == true)                        // Verifica se a variável "previousDisabled" é verdadeira
                {
                    if (currentTrack < 1)                       // Verifica se a variável "currenttrack" é menor que 1
                    {
                        currentTrack = quantityOfTracks;        // Atribui o valor da variável "quantityOfTracks" a variável "currentTrack"
                    }
                }
                else
                {
                    if (currentTrack == 1)                              // verifica se a variável "currentTrack" é igual a 1
                    {
                        previousDisabled = true;                        // A variável "previousDisabled" se torna verdadeira
                        AudioPreviousIndicator.write(previousDisabled); // Escreve no "LcmVar" "AudioPreviousIndicator" o valor da variável "previousDisabled"
                    }
                }
                AudioCurrentTrackIndicator.write(currentTrack); // Escreve no "LcmVar" "AudioCurrentTrackIndicator" o valor da variável "currentTrack"
            }
            if (nextDisabled == true)                           // Verifica se a variável "nextDisabled" é verdadeira
            {
                nextDisabled = false;                           // A variável "nextDisabled" se torna falso
                AudioNextIndicator.write(nextDisabled);         // Escreve no "LcmVar" "AudioNextIndicator" o valor da variável "nextDisabled"
            }
            break;

        case audioControlsPlayPause:                            // Caso o valor da variável "value" seja o "Return Value" "audioControlsPlayPause"
            if (isPlaying == false)                             // Verifica se a variável "isPlaying" é falsa
            {
                isPlaying = true;                               // A variável "inMuted" se torna verdadeira
                isStopped = false;                              // A variável "isStopped" se torna falso
            }
            else
            {
                isPlaying = false;                              // A variável "isPlaying" se torna falso
            }
            AudioPlayPauseIndicator.write(isPlaying);           // Escreve no "LcmVar" "AudioPlayPauseIndicator" o valor da variável "isPlaying"
            AudioStopIndicator.write(isStopped);                // Escreve no "LcmVar" "AudioStopIndicator" o valor da variável "isStopped"
            break;

        case audioControlsNext:                                 // Caso o valor da variável "value" seja o "Return Value" "audioControlsNext"
            if (nextDisabled == false)                          // Verifica se a variável "nextDisabled" é falsa
            {
                currentTrack++;                                 // Incrementa 1 na variável "currentTrack"
                if (isRepeating == true)                        // Verifica se a variável "isRepeating" é verdadeira
                {
                    if (currentTrack > quantityOfTracks)        // Verifica se a variável "currentTrack" é menor que a variável "quantityOfTracks"
                    {
                        currentTrack = 1;                       // Atribui 1 a variável "currentTrack"
                    }
                }
                else
                {
                    if (currentTrack == quantityOfTracks)       // Verifica se a variável "currentTrack" é igual a variável "quantityOfTracks"
                    {
                        nextDisabled = true;                    // A variável "nextDisabled" se torna verdadeira
                        AudioNextIndicator.write(nextDisabled); // Escreve no "LcmVar" "AudioNextIndicator" o valor da variável "nextDisabled"
                    }
                }
                AudioCurrentTrackIndicator.write(currentTrack); // Escreve no "LcmVar" "AudioCurrentTrackIndicator" o valor da variável "currentTrack"
            }
            if (previousDisabled == true)                       // Verifica se a variável "previousDisabled" é verdadeira
            {
                previousDisabled = false;                       // A variável "previousDisabled" se torna falso
                AudioPreviousIndicator.write(previousDisabled); // Escreve no "LcmVar" "AudioPreviousIndicator" o valor da variável "previousDisabled"
            }
            break;

        case audioControlsStop:                                 // Caso o valor da variável "value" seja o "Return Value" "audioControlsStop"
            if (isStopped == false)
            {
                isStopped = true;                               // A variável "isStopped" se torna verdadeira
                isPlaying = false;                              // A variável "isPlaying" se torna falso
            }
            AudioPlayPauseIndicator.write(isPlaying);           // Escreve no "LcmVar" "AudioPlayPauseIndicator" o valor da variável "isPlaying"
            AudioStopIndicator.write(isStopped);                // Escreve no "LcmVar" "AudioStopIndicator" o valor da variável "isStopped"
            break;

        default:
            break;
        }
    }

    /*
     * Término do código da tela principal (PicId 10 - main)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de volume (PicId 9 - Volume)
     */

    if (AudioVolume.available())                                    // Verifica se chegou algo no "LcmVar" "AudioVolume"
    {
        volume = AudioVolume.getData();                             // Atribui o valor recebido do "LcmVar" "AudioVolume" a variável "volume"
    }

    /*
     * Término do código da tela de volume (PicId 9 - Volume)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de RTC (PicId 2 - RTC)
     */

    if (RtcButtons.available())                                     // Verifica se chegou algo no "LcmVar" "RtcButtons"
    {
        int value = RtcButtons.getData();                           // Atribui o valor recebido a variável "value"
        keyboardIsOpen = true;                                      // A variável "keyboardIsOpen" se torna verdadeira
        lastKeyboardResponseTime = millis() + keyboardIsOpenReadIntervalInMs;// Atribui o valor de "millis()" somado ao valor da variável "keyboardIsOpenReadIntervalInMs" a variável "lastKeyboardResponseTime"
        currentRtcKeyboard = rtcKeyboardSequenceNone;               // A variável "currentRtcKeyboard" recebe o valor da variável "rtcKeyboardSequenceNone"

        switch (value)                                              // Verifica qual dos "Return Values" dos botões de configuração do RTC que foi atribuido a variável "value"
		{
        case rtcButtonDay:                                          // Caso o valor da variável "value" seja o "Return Value" "rtcButtonDay"
            Lcm.activateSoftwareControl(softwareControlCodeDay);    // Ativa o teclado de configuração do dia do RTC
            RtcSelectedIcons.write(rtcSelectedIconDay);             // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconDay"
            break;

        case rtcButtonMonth:                                        // Caso o valor da variável "value" seja o "Return Value" "rtcButtonMonth"
            Lcm.activateSoftwareControl(softwareControlCodeMonth);  // Ativa o teclado de configuração do mês do RTC
            RtcSelectedIcons.write(rtcSelectedIconMonth);           // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconMonth"
            break;

        case rtcButtonYear:                                         // Caso o valor da variável "value" seja o "Return Value" "rtcButtonYear"
            Lcm.activateSoftwareControl(softwareControlCodeYear);   // Ativa o teclado de configuração do ano do RTC
            RtcSelectedIcons.write(rtcSelectedIconYear);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconYear"
            break;

        case rtcButtonHour:                                         // Caso o valor da variável "value" seja o "Return Value" "rtcButtonHour"
            Lcm.activateSoftwareControl(softwareControlCodeHour);   // Ativa o teclado de configuração da hora do RTC
            RtcSelectedIcons.write(rtcSelectedIconHour);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconHour"
            break;

        case rtcButtonMinute:                                       // Caso o valor da variável "value" seja o "Return Value" "rtcButtonMinute"
            Lcm.activateSoftwareControl(softwareControlCodeMinute); // Ativa o teclado de configuração do minuto do RTC
            RtcSelectedIcons.write(rtcSelectedIconMinute);          // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconMinute"
            break;

        case rtcButtonSecond:                                       // Caso o valor da variável "value" seja o "Return Value" "rtcButtonSecond"
            Lcm.activateSoftwareControl(softwareControlCodeSecond); // Ativa o teclado de configuração do segundo do RTC
            RtcSelectedIcons.write(rtcSelectedIconSecond);          // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconSecond"
            break;

        case rtcButtonDate:                                         // Caso o valor da variável "value" seja o "Return Value" "rtcButtonDate"
            Lcm.activateSoftwareControl(softwareControlCodeDay);    // Ativa o teclado de configuração do dia do RTC
            RtcSelectedIcons.write(rtcSelectedIconDay);             // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconDay"
            currentRtcKeyboard = rtcKeyboardSequenceDay;            // Atribui o valor da variável "rtcKeyboardSequenceDay" a variável "currentRtcKeyboard"
            break;

        case rtcButtonTime:                                         // Caso o valor da variável "value" seja o "Return Value" "rtcButtonTime"
            Lcm.activateSoftwareControl(softwareControlCodeHour);   // Ativa o teclado de configuração da hora do RTC
            RtcSelectedIcons.write(rtcSelectedIconHour);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconHour"
            currentRtcKeyboard = rtcKeyboardSequenceHour;           // Atribui o valor davariável "rtcKeyboardSequenceHour" a variável "currentRtcKeyboard"
            break;

        default:
            break;
        }
    }

    if (KeyboardDay.available())                                    // Verifica se chegou algo no "LcmVar" "KeyboardDay"
    {
        lastRtcDay = KeyboardDay.getData();                         // Atribui o valor recebido pelo "LcmVar" "KeyboardDay" a variável "lastRtcDay"

        if (currentRtcKeyboard == rtcKeyboardSequenceDay)           // Verifica se a variável "currentRtcKeyboard" é igual a variável "rtcKeyboardSequenceDay"
        {
            Lcm.activateSoftwareControl(softwareControlCodeMonth);  // Ativa o teclado de configuração do mês do RTC
            RtcSelectedIcons.write(rtcSelectedIconMonth);           // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconMonth"
            currentRtcKeyboard = rtcKeyboardSequenceMonth;          // Atribui o valor davariável "rtcKeyboardSequenceMonth" a variável "currentRtcKeyboard"
        }
        else
        {
            RtcSelectedIcons.write(rtcSelectedIconNone);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconNone"
            Lcm.rtcWriteDay(lastRtcDay);                            // Atribui o valor da variável "lastRtcDay" no valor do dia no RTC do display
        }
    }

    if (KeyboardMonth.available())                                  // Verifica se chegou algo no "LcmVar" "KeyboardMonth"
    {
        lastRtcMonth = KeyboardMonth.getData();                     // Atribui o valor recebido pelo "LcmVar" "KeyboardMonth" a variável "lastRtcMonth"

        if (currentRtcKeyboard == rtcKeyboardSequenceMonth)         // Verifica se a variável "currentRtcKeyboard" é igual a variável "rtcKeyboardSequenceMonth"
        {
            Lcm.activateSoftwareControl(softwareControlCodeYear);   // Ativa o teclado de configuração do ano do RTC
            RtcSelectedIcons.write(rtcSelectedIconYear);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconYear"
            currentRtcKeyboard = rtcKeyboardSequenceYear;           // Atribui o valor davariável "rtcKeyboardSequenceYear" a variável "currentRtcKeyboard"
        }
        else
        {
            RtcSelectedIcons.write(rtcSelectedIconNone);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconNone"
            Lcm.rtcWriteMonth(lastRtcMonth);                        // Atribui o valor da variável "lastRtcMonth" no valor do mês no RTC do display
        }
    }

    if (KeyboardYear.available())                                   // Verifica se chegou algo no "LcmVar" KeyboardYear"
    {
        lastRtcYear = KeyboardYear.getData();                       // Atribui o valor recebido pelo "LcmVar" "KeyboardYear" a variável "lastRtcYear"

        if (currentRtcKeyboard == rtcKeyboardSequenceYear)          // Verifica se a variável "currentRtcKeyboard" é igual a variável "rtcKeyboardSequenceYear"
        {
            Lcm.rtcWriteDate(lastRtcDay, lastRtcMonth, lastRtcYear);// Atribui os valores das variáveis "lastRtcDay", "lastRtcMonth" e "lastRtcYear" nos valores de dia, mês e ano no RTC do display
            currentRtcKeyboard = rtcKeyboardSequenceNone;           // Atribui o valor davariável "rtcKeyboardSequenceNone" a variável "currentRtcKeyboard"
        }
        else
        {
            Lcm.rtcWriteYear(lastRtcYear);                          // Atribui o valor da variável "lastRtcYear" no valor do ano no RTC do display
        }
        RtcSelectedIcons.write(rtcSelectedIconNone);                // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconNone"
    }

    if (KeyboardHour.available())                                   // Verifica se chegou algo no "LcmVar" KeyboardHour"
    {
        lastRtcHour = KeyboardHour.getData();                       // Atribui o valor recebido pelo "LcmVar" "KeyboardHour" a variável "lastRtcHour"

        if (currentRtcKeyboard == rtcKeyboardSequenceHour)          // Verifica se a variável "currentRtcKeyboard" é igual a variável "rtcKeyboardSequenceHour"
        {
            Lcm.activateSoftwareControl(softwareControlCodeMinute); // Ativa o teclado de configuração do minuto do RTC
            RtcSelectedIcons.write(rtcSelectedIconMinute);          // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconMinute"
            currentRtcKeyboard = rtcKeyboardSequenceMinute;         // Atribui o valor davariável "rtcKeyboardSequenceMinute" a variável "currentRtcKeyboard"
        }
        else
        {
            RtcSelectedIcons.write(rtcSelectedIconNone);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconNone"
            Lcm.rtcWriteHour(lastRtcHour);                          // Atribui o valor da variável "lastRtcHour" no valor da hora no RTC do display
        }
    }

    if (KeyboardMinute.available())                                 // Verifica se chegou algo no "LcmVar" KeyboardMinute"
    {
        lastRtcMinute = KeyboardMinute.getData();                   // Atribui o valor recebido pelo "LcmVar" "KeyboardMinute" a variável "lastRtcMinute"

        if (currentRtcKeyboard == rtcKeyboardSequenceMinute)        // Verifica se a variável "currentRtcKeyboard" é igual a variável "rtcKeyboardSequenceMinute"
        {
            Lcm.activateSoftwareControl(softwareControlCodeSecond); // Ativa o teclado de configuração do segundo do RTC
            RtcSelectedIcons.write(rtcSelectedIconSecond);          // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconSecond"
            currentRtcKeyboard = rtcKeyboardSequenceSecond;         // Atribui o valor da variável "rtcKeyboardSequenceSecond" a variável "currentRtcKeyboard"
        }
        else
        {
            RtcSelectedIcons.write(rtcSelectedIconNone);            // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconNone"
            Lcm.rtcWriteMinute(lastRtcMinute);                      // Atribui o valor da variável "lastRtcMinute" no valor do minuto no RTC do display
        }
    }

    if (KeyboardSecond.available())                                 // Verifica se chegou algo no "LcmVar" KeyboardSecond"
    {
        lastRtcSecond = KeyboardSecond.getData();                   // Atribui o valor recebido pelo "LcmVar" "KeyboardSecond" a variável "lastRtcSecond"

        if (currentRtcKeyboard == rtcKeyboardSequenceSecond)        // Verifica se a variável "currentRtcKeyboard" é igual a variável "rtcKeyboardSequenceSecond"
        {
            Lcm.rtcWriteClock(lastRtcHour, lastRtcMinute, lastRtcSecond);// Atribui os valores das variáveis "lastRtcHour", "lastRtcMinute" e "lastRtcSecond" nos valores de hora, minuto e segundo no RTC do display
            currentRtcKeyboard = rtcKeyboardSequenceNone;           // Atribui o valor da variável "rtcKeyboardSequenceNone" a variável "currentRtcKeyboard"
        }
        else
        {
            Lcm.rtcWriteSecond(lastRtcSecond);                      // Atribui o valor da variável "lastRtcSecond" no valor do segundo no RTC do display
        }
        RtcSelectedIcons.write(rtcSelectedIconNone);                // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconNone"
    }

    if (keyboardIsOpen == true)                                     // Verifica se a variável "keyboardIsOpen" é verdadeira
    {
        if (lastKeyboardResponseTime < millis())                    // Verifica se a variável "lastKeyboardResponseTime" é menor que "millis()"
        {
            keyboardIsOpen = Lcm.readKeyboardStatus();              // Atribui o estado atual do teclado a variável "keyboardIsOpen"
            if (keyboardIsOpen == false)                            // Verifica se a variável "keyboardIsOpen" é falsa
            {
                RtcSelectedIcons.write(rtcSelectedIconNone);        // Escreve no "LcmVar" "RtcSelectedIcons" o valor da variável "rtcSelectedIconNone"
            }
            lastKeyboardResponseTime = millis() + keyboardIsOpenReadIntervalInMs;// Atribui o valor de "millis()" somado ao valor da variável "keyboardIsOpenReadIntervalInMs" a variável "lastKeyboardResponseTime"
        }
    }

    /*
     * Término do código da tela de RTC (PicId 2 - RTC)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de curva A0 (PicId 3 - CurveA0)
     */

    if (CurveA0Controls.available())                                // Verifica se chegou algo no "LcmVar" "CurveA0Controls"
    {
        int value = CurveA0Controls.getData();                      // Atribui o valor recebido pelo "LcmVar" "CurveA0Controls" a variável "value"

        switch (value)                                              // Verifica qual dos "Return Values" dos controles da tela curva A0 (PicId 3 - CurveA0) que foi atribuido a variável "value"
        {
        case curveA0ControlPlay:                                    // Caso o valor da variável "value" seja o "Return Value" "curveA0ControlPlay"
            curveA0isPlotting = true;                               // A variável "curveA0isPlotting" se torna verdadeira
            break;

        case curveA0ControlPause:                                   // Caso o valor da variável "value" seja o "Return Value" "curveA0ControlPause"
            curveA0isPlotting = false;                              // A variável "curveA0isPlotting" se torna falso
            break;

        case curveA0ControlStop:                                    // Caso o valor da variável "value" seja o "Return Value" "curveA0ControlStop"
            Lcm.clearTrendCurve0();                                 // Apaga todos os pontos do "Trend Curve Display" do canal "0"
            curveA0isPlotting = false;                              // A variável "curveA0isPlotting" se torna falso
            break;

        default:
            break;
        }
    }

    if (curveA0isPlotting == true)                                  // Verifica se a variável "curveA0isPlotting" é verdadeira
    {
        if (lastCurveA0WriteTime < millis())                        // Verifica se a variável "lastCurveA0WriteTime" é menor que "millis()"
        {
            float value = analogRead(curveA0AnalogPin);             // Atribui o valor analógico que foi lido do pino "curveA0AnalogPin" a variável "value"
            value = (value * 100) / 1023;                           // Cálculo para fazer o valor de value ficar entre 0 e 100

            Lcm.writeTrendCurve0(value);                            // Envia o valor da variável "value" para o canal 0 do "trend Curve Display"

            CurveA0TemperatureIndicator.write((int)(value));        // Escreve no "LcmVar" "CurveA0TemperatureIndicator" o valor da variável "value"

            lastCurveA0WriteTime = millis() + curveA0WriteIntervalInMs;// Atribui o valor de "millis()" somado ao valor da variável "curveA0WriteIntervalInMs" a variável "lastCurveA0WriteTime"
        }
    }

    /*
     * Término do código da tela de curva A0 (PicId 3 - CurveA0)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de simulação da curva (PicId 4 - CurveSim)
     */

    if (CurveSimulationSampleButtons.available())                   // Verifica se chegou algo no "LcmVar" "CurveSimulationSampleButtons"
    {
        int value = CurveSimulationSampleButtons.getData();         // Atribui o valor recebido pelo "LcmVar" "CurveSimulationSampleButtons" a variável "value"

        switch (value)                                              // Verifica qual dos "Return Values" dos botões de simulação de curva foi atribuido a variável "value"
        {
        case curveSimulationSampleEcg:                              // Caso o valor da variável "value" seja o "Return Value" "curveSimulationSampleEcg"
        {
            int ecgSampleIndex = 0;                                 // Atribui o valor "0" a variável "ecgSampleIndex"

            for (int curveCurrentPoint = 0; curveCurrentPoint <= curveNumberOfPoints; curveCurrentPoint++)
            {
                Lcm.writeTrendCurve1(ecgSamplePoints[ecgSampleIndex]);  // Envia o valor da variável "ecgSamplePoints[ecgSampleIndex]" para o canal 1 do "trend Curve Display"
                CurveSimulationTemperatureIndicator.write(ecgSamplePoints[ecgSampleIndex]); // Escreve no "LcmVar" "CurveSimulationTemperatureIndicator" o valor da variável "ecgSamplePoints[ecgSampleIndex]"
                CurveSimulationManualInput.write(ecgSamplePoints[ecgSampleIndex]);  // Escreve no "LcmVar" "CurveSimulationManualInput" o valor da variável "ecgSamplePoints[ecgSampleIndex]"
                ecgSampleIndex++;
                if (ecgSampleIndex == ecgSamplePointsLength)              // Verifica se a variável "ecgSampleIndex" é igual a vaiável "ecgSamplePointsLength"
                {
                    ecgSampleIndex = 0;                                     // Atribui o valor "0" a variavel "ecgSampleIndex"
                }
            }
        }
        break;

        case curveSimulationSampleSine:                             // Caso o valor da variável "value" seja o "Return Value" "curveSimulationSampleSine"
        {
            float angleInRad = 0;                                       // Cria a variável "angleInRad" e atribui o valor "0" a ela
            double sine;                                                // Cria a variável "sine"
            const float angleStep = 0.1;                                // Cria a variável "angleStep" e atribui o valor "0.1" a ela

            for (int curveCurrentPoint = 0; curveCurrentPoint <= curveNumberOfPoints; ++curveCurrentPoint)
            {
                sine = sin(angleInRad);                                   // Atribui o seno do valor da variável "angleInRad" a variável "sine"
                sine = (sine + 1) * 50;                                   // Calculo para colocar o valor da variável "sine" entre 0 e 100
                Lcm.writeTrendCurve1(sine);                               // Envia o valor da variável "sine" para o canal 1 do "trend Curve Display"
                angleInRad += angleStep;                                  // Incrementa o valor da variável "angleStep" a variável "angleInRad"
                CurveSimulationTemperatureIndicator.write((uint8_t)sine); // Escreve no "LcmVar" "CurveSimulationTemperatureIndicator" o valor da variável "sine"
                CurveSimulationManualInput.write((uint8_t)sine);          // Escreve no "LcmVar" "CurveSimulationManualInput" o valor da variável "sine"
            }
        }
        break;

        default:
            break;
        }
    }

    if (CurveSimulationManualInput.available())                     // Verifica se chegou algo no "LcmVar" "CurveSimulationManualInput"
    {
        int value = CurveSimulationManualInput.getData();           // Atribui o valor recebido pelo "LcmVar" "CurveSimulationManualInput" a variável "value"
        Lcm.writeTrendCurve1(value);								// Envia o valor da variável "value" para o canal 1 do "trend Curve Display"
        CurveSimulationTemperatureIndicator.write(value);           // Escreve no "LcmVar" "CurveSimulationTemperatureIndicator" o valor da variável "value"
    }

    /*
     * Término do código da tela de simulação da curva (PicId 4 - CurveSim)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de pressão (PicId 5 - Pressure)
     */

    if (PressureSetpoint.available())                               // Verifica se chegou algo no "LcmVar" "PressureSetpoint"
    {
        adjustPressure = true;                                      // A variável "adjustPressure" se torna verdadeira
        pressureSetpointValue = PressureSetpoint.getData();         // Atribui o valor recebido pelo "LcmVar" "PressureSetpoint" a variável "pressureSetpointValue"
    }

    if (adjustPressure == true)                                     // Verifica se a variável "adjustPressure" é verdadeira
    {
        if (lastPressureWriteTime < millis())                       // Verifica se a variável "lastPressureWriteTime" é menor que "millis()"
        {
            if (pressureSetpointValue > currentPressureValue)       // Verifica se a variável "pressureSetpointValue" é maior que a variável"currentPressureValue"
            {
                currentPressureValue++;                             // Incrementa "1" a variável "currentPressureValue"
            }
            else if (pressureSetpointValue < currentPressureValue)  // Verifica se a variável "pressureSetpointValue" é menor que a variável"currentPressureValue"
            {
                currentPressureValue--;                             // Decrementa "1" da variável "currentPressureValue"
            }

            if (pressureSetpointValue == currentPressureValue)      // Verifica se a variável "pressureSetpointValue" é igual a variável "currentPressureValue"
            {
                adjustPressure = false;                             // A variável "adjustPressure" se torna falso
            }

            if (currentPressureValue >= pressureAlertLevel)         // Verifica se a variável "currentPressureValue" é maior ou igual a variável "pressureAlertLevel"
            {
                PressureAlertIndicator.write(1);                    // Escreve no "LcmVar" "PressureAlertIndicator" o valor da variável "1"
            }
            else
            {
                PressureAlertIndicator.write(0);                    // Escreve no "LcmVar" "PressureAlertIndicator" o valor da variável "0"
            }

            CurrentPressureIndicator.write(currentPressureValue);   // Escreve no "LcmVar" "CurrentPressureIndicator" o valor da variável "currentPressureValue"
            lastPressureWriteTime = millis() + pressureWriteIntervalInMs;// Atribui o valor de "millis()" somado ao valor da variável "pressureWriteIntervalInMs" a variável "lastPressureWriteTime"
        }
    }

    /*
     * Término do código da tela de pressão (PicId 5 - Pressure)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de LED (PicId 6 - Led)
     */

    if (LedControls.available())                                    // Verifica se chegou algo no "LcmVar" "LedControls"
    {
        int value = LedControls.getData();                          // Atribui o valor recebido a variável "value"

        switch (value)                                              // Verifica qual dos "Return Values" dos botões de controle de led foi atribuido a variável "value"
        {
        case ledControlsToggleLed1:                                 // Caso o valor da variável "value" seja o "Return Value" "ledControlsToggleLed1"
            Led1Indicator.request();                                // Pede para o "LcmVar" "Led1Indicator" o seu valor
            break;

        case ledControlsToggleLed2:                                 // Caso o valor da variável "value" seja o "Return Value" "ledControlsToggleLed2"
            Led2Indicator.request();                                // Pede para o "LcmVar" "Led2Indicator" o seu valor
            break;

        case ledControlsToggleLed3:                                 // Caso o valor da variável "value" seja o "Return Value" "ledControlsToggleLed3"
            Led3Indicator.request();                                // Pede para o "LcmVar" "Led3Indicator" o seu valor
            break;

        case ledControlsToggleLed4:                                 // Caso o valor da variável "value" seja o "Return Value" "ledControlsToggleLed4"
            Led4Indicator.request();                                // Pede para o "LcmVar" "Led4Indicator" o seu valor
            break;

        case ledControlsSetAllLedsToLow:							// Caso o valor da variável "value" seja o "Return Value" "ledControlsSetAllLedsToLow"
            Led1Indicator.write(LOW);                               // Escreve no "LcmVar" "Led1Indicator" o valor "LOW" - Desligado
            Led2Indicator.write(LOW);                               // Escreve no "LcmVar" "Led2Indicator" o valor "LOW" - Desligado
            Led3Indicator.write(LOW);                               // Escreve no "LcmVar" "Led3Indicator" o valor "LOW" - Desligado
            Led4Indicator.write(LOW);                               // Escreve no "LcmVar" "Led4Indicator" o valor "LOW" - Desligado
            digitalWrite(ledPin1, LOW);                             // Escreve no pino "ledPin1" o valor "LOW" - Desligado
            digitalWrite(ledPin2, LOW);                             // Escreve no pino "ledPin2" o valor "LOW" - Desligado
            digitalWrite(ledPin3, LOW);                             // Escreve no pino "ledPin3" o valor "LOW" - Desligado
            digitalWrite(ledPin4, LOW);                             // Escreve no pino "ledPin4" o valor "LOW" - Desligado
            break;

        case ledControlsToggleAllLeds:                              // Caso o valor da variável "value" seja o "Return Value" "ledControlsToggleAllLeds"
            Led1Indicator.request();
            Led2Indicator.request();
            Led3Indicator.request();
            Led4Indicator.request();
            break;

        case ledControlsSetAllLedsToHigh:                           // Caso o valor da variável "value" seja o "Return Value" "ledControlsSetAllLedsToHigh"
            Led1Indicator.write(HIGH);                              // Escreve no "LcmVar" "Led1Indicator" o valor "HIGH" - Ligado
            Led2Indicator.write(HIGH);                              // Escreve no "LcmVar" "Led2Indicator" o valor "HIGH" - Ligado
            Led3Indicator.write(HIGH);                              // Escreve no "LcmVar" "Led3Indicator" o valor "HIGH" - Ligado
            Led4Indicator.write(HIGH);                              // Escreve no "LcmVar" "Led4Indicator" o valor "HIGH" - Ligado
            digitalWrite(ledPin1, HIGH);                            // Escreve no pino "ledPin1" o valor "HIGH" - Ligado
            digitalWrite(ledPin2, HIGH);                            // Escreve no pino "ledPin2" o valor "HIGH" - Ligado
            digitalWrite(ledPin3, HIGH);                            // Escreve no pino "ledPin3" o valor "HIGH" - Ligado
            digitalWrite(ledPin4, HIGH);                            // Escreve no pino "ledPin4" o valor "HIGH" - Ligado
            break;

        default:
            break;
        }
    }

    if (Led1Indicator.available())                              // Verifica se chegou algo no "LcmVar" "Led1Indicator"
    {
        int value = Led1Indicator.getData();                    // Atribui o valor recebido a variável "value"
        value = !value;                                         // Inverte o valor da variavel "value"
        Led1Indicator.write(value);                             // Escreve no "LcmVar" "Led1Indicator" o valor da variável "value"
        digitalWrite(ledPin1, value);                           // Escreve no pino "ledPin1" o valor da variável "value"
    }

    if (Led2Indicator.available())                              // Verifica se chegou algo no "LcmVar" "Led2Indicator"
    {
        int value = Led2Indicator.getData();                    // Atribui o valor recebido a variável "value"
        value = !value;                                         // Inverte o valor da variavel "value"
        Led2Indicator.write(value);                             // Escreve no "LcmVar" "Led2Indicator" o valor da variável "value"
        digitalWrite(ledPin2, value);                           // Escreve no pino "ledPin2" o valor da variável "value"
    }

    if (Led3Indicator.available())                              // Verifica se chegou algo no "LcmVar" "Led3Indicator"
    {
        int value = Led3Indicator.getData();                    // Atribui o valor recebido a variável "value"
        value = !value;                                         // Inverte o valor da variavel "value"
        Led3Indicator.write(value);                             // Escreve no "LcmVar" "Led3Indicator" o valor da variável "value"
        digitalWrite(ledPin3, value);                           // Escreve no pino "ledPin3" o valor da variável "value"
    }

    if (Led4Indicator.available())                              // Verifica se chegou algo no "LcmVar" "Led4Indicator"
    {
        int value = Led4Indicator.getData();                    // Atribui o valor recebido a variável "value"
        value = !value;                                         // Inverte o valor da variavel "value"
        Led4Indicator.write(value);                             // Escreve no "LcmVar" "Led4Indicator" o valor da variável "value"
        digitalWrite(ledPin4, value);                           // Escreve no pino "ledPin4" o valor da variável "value"
    }

    /*
     * Término do código da tela de LED (PicId 6 - Led)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de texto (PicId 7 - Text)
     */

    if (TextInput.available())                              // Verifica se chegou algo no "LcmString" "TextInput"
    {
        String characters;                                  // Cria uma variável do tipo "String" com o nome "characters"
        String invertedCharacters;                          // Cria uma variável do tipo "String" com o nome "invertedCharacters"
        int characterIndex = 0;                             // Cria uma variável do tipo "int" com o nome "characterIndex" e atribui o valor "0" a ela

        while (TextInput.available())                       // Verifica e executa enquanto existir algo no "LcmString" "TextInput"
        {
            characters += (char)TextInput.getData();        // Concatena o valor recebido pelo "LcmString" "TextInput" a String "characters"
            characterIndex++;                               // Incrementa "1" a variavel "characterIndex"
        }

        while (characterIndex)                                  // Verifica e executa enquanto o valor da variável "characterIndex" for maior que "0"
        {
            characterIndex--;                                   // Decrementa "1" da variável "characterIndex"
            invertedCharacters += characters[characterIndex];   // Concatena os caracteres da variável "characters" a String "characters"
        }
        InvertedText.write(invertedCharacters);             // Escreve no "LcmString" "InvertedText" o valor da variável "invertedCharacters"
    }

    /*
     * Término do código da tela de texto (PicId 7 - Text)
     *******************************************************************************************************************************************/

    /*******************************************************************************************************************************************
     * Início do código da tela de ajustes  (PicId 8 - Settings)
     */

    if (BackLight.available())                              // Verifica se chegou algo no "LcmVar" "BackLight"
    {
        int value = BackLight.getData();                    // Atribui o valor recebido a variável "value"
        Lcm.changeBacklight(value);                         // Altera o valor do "Backlight" do "lcm" para o valor da variável "value"
    }

    if (ReadVersionButton.available())                      // Verifica se chegou algo no "LcmVar" "ReadVersionButton"
    {
        ReadVersionButton.getData();                        // Realiza a leitura do que chegou no "LcmVar" "ReadVersionButton" mas o valor recebido não é usado
        int value = Lcm.readFirmwareVersion();              // Verifica qual a versão do firmware do display e atribui a variável "value"
		value = (value - (6 * (value >> 4)));				// Realiza a conversão de BCD para inteiro. 0x28 BCD -> 28 inteiro
        VersionIndicator.write(value);                      // Escreve no "LcmVar" "VersionIndicator" o valor da variável "value"
    }

    if (ActivateBuzzerButton.available())                   // Verifica se chegou algo no "LcmVar" "ActivateBuzzerButton"
    {
        ActivateBuzzerButton.getData();                     // Realiza a leitura do que chegou no "LcmVar" "ActivateBuzzerButton" mas o valor recebido não é usado
        int value = BuzzerActivationTime.read();            // Verifica qual o valor que foi configurado do campo "Buzzer" da tela de ajustes (PicId 8 - Settings) e atribui a variável "value"
        Lcm.beepBuzzer(value);                              // Ativa o buzzer de acordo com o valor da variável "value"(Milissegundo)
    }

    if (CalibrateButton.available())                        // Verifica se chegou algo no "LcmVar" "CalibrateButton"
    {
        int value = CalibrateButton.getData();              // Atribui o valor recebido a variável "value"
        if (value == popupConfirm)                          // Verifica se o valor da variável "value" é igual a variável "popupConfirm"
        {
            Lcm.calibrate();                                // Inicia o processo de calibração do Display
        }
    }

    if (ResetButton.available())                            // Verifica se chegou algo no "LcmVar" "ResetButton"
    {
        int value = ResetButton.getData();                  // Atribui o valor recebido a variável "value"
        if (value == popupConfirm)                          // Verifica se o valor da variável "value" é igual a variável "popupConfirm"
        {
            Lcm.resetLCM();                                 // Reseta o Display
        }
    }

    /*
     * Término do código da tela de ajustes (PicId 8 - Settings)
     *******************************************************************************************************************************************/
}
