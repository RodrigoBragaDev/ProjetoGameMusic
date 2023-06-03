/*

  iot.Board - LAPIN
  Daniel Almeida Chagas

  Entradas:
  - Joystick nos pinos 14 e 15
  - Botão no pino 13
  - Touch 7, 8 e 9 (usar touchRead(T7))
  - Display OLED no endereço 0x3C

*/

#include <GyverOLED.h>
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled; //para display pequeno 0.96"
GyverOLED<SSH1106_128x64> oled; //para display médio 1.3"

const int joystick_x = 14;
const int joystick_y = 15;
const int button = 13;

const uint8_t unifor[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC,
0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xF0,
0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xF8,
0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3C, 0x7C, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x81, 0x80, 0x80,
0xC0, 0xC0, 0xC0, 0xC1, 0x81, 0x81, 0x81, 0x83, 0x03, 0x07, 0x07, 0x0F, 0x1F, 0x3F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7C, 0x3C, 0x38, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0x3F, 0x03, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF8, 0xFC, 0x7E, 0x3F, 0x1F, 0x0F, 0x8F, 0x87,
0x87, 0x87, 0x87, 0x87, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x3E, 0xFC, 0xF8, 0xF0, 0xE0, 0x83,
0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3F, 0xFF, 0xFF, 0xFF,
0xFF, 0xFE, 0xC0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF7, 0xF8, 0xFE, 0x7E, 0x1F, 0x1F, 0x8F, 0x8F,
0x8F, 0x8F, 0x8F, 0x8F, 0x1F, 0x1F, 0x7F, 0xFE, 0xFC, 0xF8, 0xE0, 0x00, 0x03, 0xFF, 0xFF, 0xFF,
0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x3C, 0x3E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0x7E, 0x7E, 0x3E, 0x1C, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0F,
0x0F, 0x1F, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F,
0x1F, 0x0F, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x1F, 0x1F, 0x3F,
0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x0F, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Change this depending on where you put your piezo buzzer
int TONE_OUTPUT_PIN = 2;
int TONE_OUTPUT_PIN2 = 17;

// The ESP32 has 16 channels which can generate 16 independent waveforms
// We'll just choose PWM channel 0 here
const int TONE_PWM_CHANNEL = 0;
const int TONE_PWM_CHANNEL2 = 1;

int tela = 0;
long timer = 0;
long timerBarra = 0;

//variaveis do jogo
int posicaoBarra = 1; //vai de 0 a 3
int barraInicio = 1; //vai de 0 a 1;
int posicaoPlayer = 0;

bool n0 = false; //nota 0 apta a ser pressionada
bool n1 = false; //nota 1 apta a ser pressionada
bool n2 = false; //nota 2 apta a ser pressionada
bool n3 = false; //nota 3 apta a ser pressionada

int tempoNoHitZone = 0;

float score = 0; //pontuação final do jogador
int posPerf = 0; //posicao na tela que dá perfect
int posGood = 0; //posicao na tela que dá good
int ponto = 0; //pontuação por nota
float sumPerf = 0; //soma de perfects
float sumGood = 0; //soma de goods
int sumMiss = 0; //soma de misses
float maxCombo = 0; //max combo
int consec = 0; //notas consecutivas
int pNaTela = 0; //mantem o perfect na tela
int gNaTela = 0; //mantem o good na tela
int mNaTela = 0; //mantem o miss na tela
int gameplay = 2;
int velo = 0;
int veloNmb = 19;
int veloHgd = 34;
int dur = 0;
int durNmb = 20;
int durHgd = 24;
int maxScore = 0;
int maxScoreHgd = 4860; //4320+
int maxScoreNmb = 14760; //13120+1640

//int score = ((sumPerf*2 + sumGood)*95+combo*5)/100; VAI SER IMPLEMENTADO EM BREVE

int posicaoNota = 0; //define onde está na musica

byte* musica;
int qtdNotas = 0;
int qtdNotasHgd = 43;
int qtdNotasNmb = 84;


byte musicaEasy[] {
  //HUNGARIAN DANCE - EASY
  B00000000,
  B01000000, //1
  B01000000, //2
  B00100000, //3
  B00100000, //4
  B10000000, //5
  B10000000, //7
  B00100000, //8
  B00010000, //9
  B00100000, //10
  B10000000, //11
  B01000000, //12
  B10000000, //13
  B00100000, //14
  B00100000, //15
  B00010000, //16
  B01000000, //17
  B01000000, //18
  B01000000, //19
  B00100000, //20
  B00100000, //21
  B00100000, //22
  B10000000, //23
  B00010000, //24
  B10000000, //25
  B01000000, //26
  B01000000, //27
  B00100000, //28
  B00010000, //29
};

byte musicaHard[] {
  //NUMB LINKIN PARK - HARD
  B00000000,
  B01000000, //1
  B01000000, //2
  B00100000, //3
  B00100000, //4
  B10000000, //5
  B10000000, //6
  B10000000, //7
  B00100000, //8
  B00010000, //9
  B00100000, //10
  B10000000, //11
  B01000000, //12
  B10000000, //13
  B00100000, //14
  B00100000, //15
  B00010000, //16
  B01000000, //17
  B01000000, //18
  B01000000, //19
  B00100000, //20
  B00100000, //21
  B00100000, //22
  B10000000, //23
  B00010000, //24
  B10000000, //25
  B01000000, //26
  B01000000, //27
  B00100000, //28
  B00010000, //29
  B01000000, //30
  B01000000, //31
  B00100000, //32
  B00100000, //33
  B10000000, //34
  B10000000, //35
  B10000000, //36
  B00100000, //37
  B00010000, //38
  B00100000, //39
  B10000000, //40
  B01000000, //41
  B10000000, //42
  B00100000, //43
  B00100000, //44
  B00010000, //45
  B01000000, //46
  B01000000, //47
  B01000000, //48
  B00100000, //49
  B00100000, //50
  B00100000, //51
  B10000000, //52
  B00010000, //53
  B10000000, //54
  B01000000, //55
  B01000000, //56
  B00100000, //57
  B00010000, //58
  B01000000, //59
  B01000000, //60
  B00100000, //61
  B00100000, //62
  B10000000, //63
  B10000000, //64
  B10000000, //65
  B00100000, //66
  B00010000, //67
  B00100000, //68
  B10000000, //69
  B01000000, //70
  B10000000, //71
  B00100000, //72
  B00100000, //73
  B00010000, //74
  B01000000, //75
  B01000000, //76
  B01000000, //77
  B00100000, //78
  B00100000, //79
  B00100000, //80
  B10000000, //81
  B00010000, //82
  B10000000, //83
};


//cursor de mouse
int pos_x = 64;
int pos_y = 32;

void setup() {
  pinMode(button, INPUT_PULLUP);
  Serial.begin(115200);
  oled.init();
  oled.home();
  oled.setScale(1);
  oled.invertText(false);
  oled.autoPrintln(true);
  Wire.setClock(700000L);   // макс. 800'000
  telaUnifor();
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcAttachPin(TONE_OUTPUT_PIN2, TONE_PWM_CHANNEL2);

  musica = musicaHard;
  velo = veloNmb;
  dur = durNmb;
  maxScore = maxScoreNmb;
  qtdNotas = qtdNotasNmb;

  xTaskCreatePinnedToCore (
    loop2,     // Function to implement the task
    "loop2",   // Name of the task
    5000,      // Stack size in bytes
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

}


void loop() {

  if(timer<millis()){
    timer = millis() + 50;
      //Serial.print("Misses");
      //Serial.print(sumMiss);
      //Serial.println();
    //funções desenham cada elemento do jogo
    if (gameplay==1){
      oled.clear();
      funcBarra(); //desenha barra inferior
      desenhaTelaToda(posicaoNota);
      posicaoNota++;
      if (digitalRead(13)==LOW && gameplay==1){ //aparece o efeito apenas quando pressiona o botão
        touchNota();
      }

      if(n0 && posicaoBarra==0 &&(digitalRead(13)==LOW) && posGood){ //condição nota 0 dar Good
        good();

      } else if (n0 && posicaoBarra==0 &&(digitalRead(13)==LOW) && posPerf){ //condição nota 0 dar Perfect
        perfect();

      }

      if(n1 && posicaoBarra==1 &&(digitalRead(13)==LOW) && posGood){ //condição nota 1 dar Good
        good();
      } else if (n1 && posicaoBarra==1 &&(digitalRead(13)==LOW) && posPerf){ //condição nota 1 dar Perfect
        perfect();
      }

      if(n2 && posicaoBarra==2 &&(digitalRead(13)==LOW) && posGood){ //condição nota 2 dar Good
        good();
      } else if (n2 && posicaoBarra==2 &&(digitalRead(13)==LOW) && posPerf){ //condição nota 2 dar Perfect
        perfect();
      }

      if(n3 && posicaoBarra==3 &&(digitalRead(13)==LOW) && posGood){ //condição nota 3 dar Good
        good();
      } else if (n3 && posicaoBarra==3 &&(digitalRead(13)==LOW) && posPerf){ //condição nota 3 dar Perfect
        perfect();
      }

      if (consec>3){ //mostra o combo apenas a partir de 4 setas acertadas consecutivamente
        combo();
      }
      if (pNaTela==1){
        mostrarPerfect();
      }

      if (gNaTela ==1){
        mostrarGood();
      }

      if (mNaTela==1){
        mostrarMiss();
      }

      //testes Serial
      Serial.print("n0: ");
      Serial.print(n0);
      Serial.println();
      Serial.print("n1: ");
      Serial.print(n1);
      Serial.println();
      Serial.print("n2: ");
      Serial.print(n2);
      Serial.println();
      Serial.print("n3: ");
      Serial.print(n3);
      Serial.println();
      Serial.print("score: ");
      Serial.print(score);
      Serial.println();
      Serial.print("soma de perfects: ");
      Serial.print(sumPerf);
      Serial.println();
      Serial.print("soma de goods: ");
      Serial.print(sumGood);
      Serial.println();
      Serial.print("Misses");
      Serial.print(sumMiss);
      Serial.println();
      Serial.print("Max Combo: ");
      Serial.print(maxCombo);
      Serial.println();
      Serial.print("gameplay ");
      Serial.print(gameplay);
      Serial.print("barraInicio ");
      Serial.print(barraInicio);
      Serial.println();

      oled.update();
      posicaoPlayer = posicaoPlayer + 1; //quantos pixels a nota vai andar por frame
      //delay(10);

      if(posicaoPlayer>(qtdNotas*dur)) {
        gameplay=0;
        //fim do jogo
        telaScore();

      }
    }

    /*if(posicaoNota>sizeof(musica)) {
      telaScore();
      if (digitalRead(13)==LOW){
        posicaoNota = 0; //condição de reset da musica
      }
    } else if (posicaoNota<=sizeof(musica)){
      funcBarra();
    }*/
    if(gameplay==2){
      oled.clear();
      desenhaTelaToda(posicaoNota);
      posicaoNota++;
      telaInicio();
      oled.update();
      posicaoPlayer = posicaoPlayer + 1;
    }

  }
  //delay(2);
}
//fim do loop

void loop2(void* pvParameters) {
  
while(gameplay==2){
  if (digitalRead(13)==LOW) {
    iniciarJogo(barraInicio);
  }
}

  if (gameplay==1 && barraInicio== 0){
  /*
  //TESTE
  delay(3350);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(250);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(250);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(250);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(970);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(970);
  */


  
  //HUNGARIAN DANCE
  delay(4900);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  //ledcWriteNote(TONE_PWM_CHANNEL2, NOTE_Cs, 2);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(650);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 4);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 3);
  delay(125);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 3);
  delay(275);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 3);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(650);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 5);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(350);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(880);//DELAY PROPOSITAL
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(650);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(625);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 4);
  delay(625);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 3);
  delay(125);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 3);
  delay(275);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 3);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 3);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(650);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(215);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 5);
  delay(650);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(830);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(108.125);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(350);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(108.125);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(875);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(416);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(690);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(416);///
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Bb, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(416);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(690);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(416);///
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(416);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(274);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(416);///
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(710);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(200);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Eb, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(698);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(200);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Eb, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(698);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 4);
  delay(200);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Eb, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(416);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(250);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(450);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 4);
  delay(115);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(450);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(450);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(450);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(2000);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 0);
  delay(1);
  ledcDetachPin(2);
  while(1);
  }





  //NUMB - LINKIN PARK
  if (gameplay==1 && barraInicio== 1){
  delay(3400);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(726);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(726);///
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(1694);///  ///
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(1694);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(726);//
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(726);///
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(1694);///  ///
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(1694);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(480);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(1210);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(1210);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(1210);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5); //PONTE
  delay(3388);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(3388);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Cs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(363);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(363);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5); //REFRAO
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(1210);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5); //REFRAO 2
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(1452);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(968);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(968);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(968);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(1452);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(1694);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(363);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(363);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(363);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(363);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 5);
  delay(242);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Gs, 5);
  delay(2016);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(484);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_Fs, 5);
  delay(726);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 0);
  delay(1);
  ledcDetachPin(2);
  while(1);
}
}


void contScore(){
  score = (((sumPerf*2+sumGood)*80+(maxCombo*20))/maxScore)*1000000; //4640+580=
}

void apagarNota(int posicao){
  musica[posicao] = B00000000;
}

void telaUnifor(){
  oled.clear();
  oled.drawBitmap(0, 0, unifor, 128, 64);
  oled.update();
  delay(200);
  oled.clear();
  oled.update();
  //telaInicial();
  //delay(2000);
  //oled.clear();
  //oled.update();
  int posicaoBarra = 1; //vai de 0 a 3
  int posicaoPlayer = 0;
  int posicaoNota = 0;
}

void mostrarPerfect(){
  oled.setCursor(40,2);
  oled.setScale(1);
  oled.print("Perfect");
}

void perfect(){ //aparece perfect
  mNaTela=0;
  gNaTela=0;
  pNaTela=1;
  apagarNota(tempoNoHitZone);
  mostrarPerfect();
  oled.rect((posicaoBarra*32),63,(posicaoBarra*32)+32,59, false);
  desenhaBarra();
  touchNota();
  contScore();
  sumPerf++;
  //score +=ponto; //score contabilizado assim apenas para testes
  consec++;
  if (maxCombo<=consec){
    maxCombo = consec;
  }
}

void mostrarGood(){
  oled.setCursor(45,2);
  oled.setScale(1);
  oled.print("Good");
}

void good(){ //aparece good
  pNaTela=0;
  mNaTela=0;
  gNaTela=1;
  apagarNota(tempoNoHitZone);
  mostrarGood();
  oled.rect((posicaoBarra*32),63,(posicaoBarra*32)+32,59,false);
  desenhaBarra();
  touchNota();
  contScore();
  sumGood++;
  //score+=ponto; //score contabilizado assim apenas para testes
  consec++;
  if (maxCombo<=consec){
    maxCombo = consec;
  }
}

void mostrarMiss(){ //mostra o miss na tela
  oled.setCursor(45,2);
  oled.setScale(1);
  oled.print("Miss");
}

void miss(){ //funcao do miss
  gNaTela=0;
  pNaTela=0;
  mNaTela=1;
  sumMiss++;
  consec=0;
}

void combo(){ //aparece o combo atual na tela
  oled.setCursor(40,4);
  oled.setScale(1);
  oled.print("Combo");
  oled.setCursor(80,4);
  oled.setScale(1);
  oled.print(consec);
}

void desenhaBarra(){ //desenha barra inferior
  oled.fastLineH(59, (posicaoBarra * 32)+3, (posicaoBarra * 32)+29);
  oled.fastLineH(63, (posicaoBarra * 32)+3, (posicaoBarra * 32)+29);
  oled.dot((posicaoBarra*32)+1,61);
  oled.dot((posicaoBarra*32)+31,61);
  oled.dot((posicaoBarra*32)+2, 60);
  oled.dot((posicaoBarra*32)+2, 62);
  oled.dot((posicaoBarra*32)+30, 60);
  oled.dot((posicaoBarra*32)+30, 62);
  if (posicaoBarra ==3){
    oled.dot(127, 61);
  }
}

void funcBarra(){ //função do posicionamento da barra nas seções 0 a 3
  if(millis()>timerBarra){
    timerBarra = millis() + 101;
    if(analogRead(joystick_x)< 512) {
    //if(analogRead(joystick_x)< 1000) {
      posicaoBarra = posicaoBarra - 1;
      if(posicaoBarra < 0) posicaoBarra = 0;
    }
    if(analogRead(joystick_x)> 3608) {
    //if(analogRead(joystick_x)> 3000) {
      posicaoBarra = posicaoBarra + 1;
      if(posicaoBarra > 3) posicaoBarra = 3;
    }
  }
  desenhaBarra();
}


void desenhaNotas(int tempo,int posY){ //desenha as notas, pega o valor do bit da nota e manipula o score por nota
  byte notasAtuais = musica[tempo]; //recebe os bytes da musica naquele momento (tempo)
  if(bitRead(notasAtuais,7)) desenhaUmaNota(0,posY);
  if(bitRead(notasAtuais,6)) desenhaUmaNota(1,posY);
  if(bitRead(notasAtuais,5)) desenhaUmaNota(2,posY);
  if(bitRead(notasAtuais,4)) desenhaUmaNota(3,posY);
  if((posY>57)&&(posY<60)){
    n0 = bitRead(notasAtuais,7);
    n1 = bitRead(notasAtuais,6);
    n2 = bitRead(notasAtuais,5);
    n3 = bitRead(notasAtuais,4);
    tempoNoHitZone = tempo;
    posPerf = 0;
    posGood = 1;
  }else if((posY>=60)&&(posY<63)){
    n0 = bitRead(notasAtuais,7);
    n1 = bitRead(notasAtuais,6);
    n2 = bitRead(notasAtuais,5);
    n3 = bitRead(notasAtuais,4);
    tempoNoHitZone = tempo;
    posGood=0;
    posPerf= 1;
  }else if (posY>=63){
    posGood = 0;
    posPerf = 0;
    if(bitRead(notasAtuais,7)||bitRead(notasAtuais,6)||bitRead(notasAtuais,5)||bitRead(notasAtuais,4)){
      miss();
    }
  }
}

void desenhaTelaToda(int tempo){ //desenha as notas que aparecem na tela
  for(int i=0;i<qtdNotas;i++){
    int posY = posicaoPlayer - (i*velo); //**************DISTANCIAMENTO ENTRE NOTAS ****************************************
    if((posY>=-3)&&(posY<64)){
      desenhaNotas(i,posY);
    }
  }
}


void touchNota(){ //desenha o efeito quando pressiona o botão
    oled.fastLineV((posicaoBarra*32),63, 1);
    oled.fastLineV((posicaoBarra*32)+32,63, 1);
    oled.fastLineH(63, posicaoBarra*32,(posicaoBarra*32)+32);
    oled.fastLineV((posicaoBarra*32)+1,63,59);
    oled.fastLineV((posicaoBarra*32)+31,63,59);
    oled.fastLineH(59, posicaoBarra*32,(posicaoBarra*32)+32);
    oled.fastLineH(58, posicaoBarra*32,(posicaoBarra*32)+32);
    if (posicaoBarra==3){
      oled.fastLineV(127,63,1);
    }
}


void desenhaUmaNota(int x,int y){ //desenho de uma nota singular
  // Xis entre 0 e 3
  // Ypsilon entre 0 e 63
  oled.fastLineH(y, (x*32)+3, (x*32)+29);
  oled.fastLineH(y+2,(x*32)+3, (x*32)+29);
  oled.fastLineH(y+1,(x*32)+2, (x*32)+10);
  oled.fastLineH(y+1,(x*32)+22, (x*32)+30);
  oled.dot((x*32)+16, y+1);
}

void telaScore(){ //função que mostra tela da pontuação final do jogador
  oled.clear();
      oled.setCursor(34,0);
      oled.setScale(1);
      oled.print("Perfects");
      oled.setCursor(94,0);
      oled.print(sumPerf);
      oled.setCursor(34,2);
      oled.print("Goods");
      oled.setCursor(94,2);
      oled.print(sumGood);
      oled.setCursor(34,4);
      oled.print("Misses");
      oled.setCursor(94,4);
      oled.print(sumMiss);
      oled.setCursor(69,6);
      oled.print("Max Combo");
      oled.setCursor(94,7);
      oled.print(maxCombo);
      oled.setCursor(9,1);
      oled.setScale(3);
      if (sumMiss==0 && score>=800000){
        oled.print("S");
      } else if (sumMiss==0 && score<800000){
        oled.print("A");
      } else if (sumMiss!=0 && score>=800000){
        oled.print("A");
      } else if (sumMiss!=0 && score>=650000 && score<800000 ){
        oled.print("B");
      } else if (sumMiss!=0 && score>=500000 && score<650000){
        oled.print("C");
      } else if (sumMiss!=0 && score >=400000 && score<500000){
        oled.print("D");
      } else if (sumMiss!=0 && score<400000){
        oled.print("F");
      }
      oled.setCursor(1,6);
      oled.setScale(1);
      oled.print("Score");
      oled.setCursor(1,7);
      oled.print(score);
      oled.update();
}

void desenhaBarraInicio(){
  oled.fastLineH(56, (barraInicio * 60)+9, (barraInicio * 60)+57);
  oled.fastLineH(58, (barraInicio * 60)+15, (barraInicio * 60)+51);
}

void telaInicio(){
  oled.setCursor(10,5);
  oled.setScale(2);
  oled.print("Easy");
  oled.setCursor(70,5);
  oled.print("Hard");
  oled.setCursor(10,0);
  oled.setScale(2);
  oled.print("GameMusic");
  oled.setCursor(15,3);
  oled.setScale(1);
  oled.print("By Rodrigo Braga");
  if(analogRead(joystick_x)< 512) {
  //if(analogRead(joystick_x)< 1000) {
    barraInicio = barraInicio - 1;
    if(barraInicio < 0) barraInicio = 0;
  }
  if(analogRead(joystick_x)> 3608) {
  //if(analogRead(joystick_x)> 3000) {
    barraInicio = barraInicio + 1;
    if(barraInicio > 1) barraInicio = 1;
  }
  desenhaBarraInicio();
  if (digitalRead(13)==LOW) {
    iniciarJogo(barraInicio);
  }
}

void iniciarJogo(int opcao){
  if(opcao == 0){
    musica = musicaEasy;
    velo = veloHgd;
    dur = durHgd;
    maxScore = maxScoreHgd;
    qtdNotas = qtdNotasHgd;
    gameplay =1;
    posicaoBarra = 1; //vai de 0 a 3
    posicaoPlayer = 0;
  }
  if(opcao == 1){
    musica = musicaHard;
    velo = veloNmb;
    dur = durNmb;
    maxScore = maxScoreNmb;
    qtdNotas = qtdNotasNmb;
    gameplay = 1;
    posicaoBarra = 1; //vai de 0 a 3
    posicaoPlayer = 0;
  }
}




