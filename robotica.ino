// IRremote - Version: Latest 
#include <IRremote.h>

const unsigned long KEY_0=0x7D168BCF;
const unsigned long KEY_1=0xF7283C77;
const unsigned long KEY_2=0x757FB4DF;
const unsigned long KEY_3=0xB33B4597;
const unsigned long KEY_4=0x3C03E507;
const unsigned long KEY_5=0xE705551F;
const unsigned long KEY_6=0xA4A58EC7;
const unsigned long KEY_7=0xE2E45F7F;
const unsigned long KEY_8=0x6BACFEEF;
const unsigned long KEY_9=0xE88E91F;

const unsigned long KEY_YELLOW=0xE01F9A81;
const unsigned long KEY_BLUE=0x68E839F1;
const unsigned long KEY_RED=0x240C9161;
const unsigned long KEY_GREEN=0xA26409C9;

int RECV_PIN = 11;

int life = 3;
int points = 0;

String texto;
long randNumber;
bool gameStarted = false;

IRrecv irrecv(RECV_PIN);  
decode_results results;

void setup()
{
  for(int i = 1; i < 9; i++){
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
  if (irrecv.decode(&results)){
    pressKey(results.value);
    
    Serial.print("BUFFER: ");
    Serial.println(texto);
    Serial.println();
    
    irrecv.resume();
  }
}


void showBin(int n){
  
  for(int i = 8; i >=0 ; i--) {
    int r = n >> i;
    if(r & 1){
      digitalWrite(i + 2, HIGH);
    }else{
      digitalWrite(i + 2, LOW);
    }
  }
}

void pressKey(unsigned long KEY){
  
  if(KEY_BLUE == KEY){
    game();
  }
  
  if(gameStarted == true){
    if(KEY_RED == KEY){
      endGame();
      texto = "";
      showBin(0);
    }
    if(KEY_GREEN == KEY){
      int n = texto.toInt();
      verificaNumero(n);
    }
    if(KEY_YELLOW == KEY){
      showInfo();
    }
  }else{
    if(KEY_YELLOW == KEY){
      int result = texto.toInt();
      showBin(result);
      texto = "";
    }
    
    if(KEY_RED == KEY){
      texto = "";
      showBin(0);
    }
  }
    
  switch(KEY) {
    case KEY_0:
      texto = texto + "0";
      break;
    case KEY_1:
      texto = texto + "1";
      break;
    case KEY_2:
      texto = texto + "2";
      break;
    case KEY_3:
      texto = texto + "3";
      break;
    case KEY_4:
      texto = texto + "4";
      break;
    case KEY_5:
      texto = texto + "5";
      break;
    case KEY_6:
      texto = texto + "6";
      break;
    case KEY_7:
      texto = texto + "7";
      break;
    case KEY_8:
      texto = texto + "8";
      break;
    case KEY_9:
      texto = texto + "9";
      break;
  }
  
}

void game(){
  Serial.println("CARREGANDO...");
  if(gameStarted == false){
    for(int j = 0; j < 3; j++){
      for(int i = 1; i < 9; i++){
        digitalWrite(i, HIGH);
        delay(100);
      }
      for(int i = 8; i >= 0; i--){
        digitalWrite(i, LOW);
        delay(100);
      }
    }
  }
  
  Serial.println("JOGO INICIADO");
  Serial.println("DIGITE O NUMERO BINARIO EM DECIMAL: ");
  
  delay(400);
  
  randNumber = random(0, 255);
  showBin((int)randNumber);
  gameStarted = true;
}


void endGame(){
  for(int i = 1; i < 9; i++){
    digitalWrite(i, HIGH);
    delay(100);
  }
  for(int i = 8; i >= 0; i--){
    digitalWrite(i, LOW);
    delay(100);
  }
  Serial.println("JOGO FINALIZADO");
  gameStarted = false;
  life = 3;
  points = 0;
}


void verificaNumero(int n){
  if(randNumber == n){
    Serial.println("PARABÉNS VOCÊ ACERTOU!");
    texto = "";
    points = points + 100;
    showInfo();
    game();
  }else{
    Serial.println("RESPOSTA INCORRETA!");
    texto = "";
    life--;
    showInfo();
    if(life == 0){
      endGame();
    }
  }
  
}

void showInfo(){
  Serial.flush();
  Serial.println();
  Serial.println();
  Serial.println("JOGO DO BIRLLLLNARIO");
  Serial.println();
  Serial.print(points);
  Serial.println(" PONTOS");
  Serial.print(life);
  Serial.println(" VIDAS RESTANTES");
  
}


