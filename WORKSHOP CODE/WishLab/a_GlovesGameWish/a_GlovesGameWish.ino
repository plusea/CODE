/*
 WISH LAB code that reads input from two players, makes decision and triggers output
 */



// variables:
int paper = 0;
int scissors = 1;
int stone = 2;

int glove1 = 3;
int glove2 = 2; // ADC 2, digital 4

int gloveValue1;
int gloveValue2;

int player1;
int player2;

int loser;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT);     
  pinMode(1, OUTPUT);     
  pinMode(2, OUTPUT);     
  pinMode(glove1, INPUT);
  digitalWrite(glove1, HIGH);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
}


// the loop routine runs over and over again forever:
void loop() {
  // read values of player 1's glove and interpret move
  gloveValue1 = analogRead(glove1);
  if(gloveValue1 < 100) player1 = 1;
  if(gloveValue1 > 100 && gloveValue1 < 200) player1 = 2;
  if(gloveValue1 > 200 && gloveValue1 < 300) player1 = 3;
  if(gloveValue1 > 300) player1 = 0;

  // read values of player 2's glove and interpret move
  gloveValue2 = analogRead(glove2);
  if(gloveValue2 < 100) player2 = 1;
  if(gloveValue2 > 100 && gloveValue2 < 200) player2 = 2;
  if(gloveValue2 > 200 && gloveValue2 < 300) player2 = 3;
  if(gloveValue2 > 300) player2 = 0;

  ////// GAME ///////
  if(player1 == 1 && player2 == 1) loser = 0;
  if(player1 == 1 && player2 == 2) loser = 1;
  if(player1 == 1 && player2 == 3) loser = 2;
  if(player1 == 2 && player2 == 1) loser = 2;
  if(player1 == 2 && player2 == 2) loser = 0;
  if(player1 == 2 && player2 == 3) loser = 1;
  if(player1 == 3 && player2 == 1) loser = 1;
  if(player1 == 3 && player2 == 2) loser = 2;
  if(player1 == 3 && player2 == 3) loser = 0;

  ////// EVALUATION ///////
  if(loser == 0) {
    digitalWrite(0, HIGH);
    delay(500);
    digitalWrite(0, LOW);
    loser = 4;
  }

  if(loser == 1) {
    digitalWrite(1, HIGH);
    delay(500);
    digitalWrite(1, LOW);
    loser = 4;
  }

  if(loser == 2) {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    loser = 4;
  }

delay(100);
}


void test() {
  gloveValue1 = analogRead(glove1);
  if(gloveValue1 < 100) digitalWrite(stone, HIGH);
  else if(gloveValue1 > 100 && gloveValue1 < 200) digitalWrite(scissors, HIGH);
  else if(gloveValue1 > 200 && gloveValue1 < 300) digitalWrite(paper, HIGH);
  else {
    digitalWrite(stone, LOW);
    digitalWrite(scissors, LOW);
    digitalWrite(paper, LOW);
  }
}







