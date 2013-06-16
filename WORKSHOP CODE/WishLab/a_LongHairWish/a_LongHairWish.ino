/*WISH LAB: Lights that make long heir even more seducive
 Software PWM on Attiny45 with 4 output pins and 1 input pin to detect motion
 */

int led[]={
  0,1,3,4};
int randomPin[]={
  1,2,3,4,5,6,7,8,9,10,11,12,6,5,7,4,8,3,9,2,10,2,3,4,5,6,7,8,9,10,11,12,6,5,7,4,8,3,9,2,10,1,11,12,9,7,5,3,1,2,4,6,8,10,11,12,3,2,5,8,6,5,9,12,3,4,5};
int movementValue;
int delayTime = 3;
int r = 0;
int y = 0;
int x;
int charliePin;





void setup(){
  for (int z=0;z<4;z++){
    pinMode(led[z],OUTPUT);
  } //for z

  pinMode(2, INPUT);
  digitalWrite(2, HIGH); // no pull-up, use slider pin to GND instead
}



void loop(){
  testLoop();
}




// blink through all 12 LEDs:
void testLoop(){
  for (int i=1;i<13;i++) {
    for (int x=1;x<254;x++) spwm(x,i,1);
    for (int x=254;x>1;x--) spwm(x,i,1);
  }
}






// software PWM
void spwm(int freq,int pin,int sp){
  // call charlieplexing to set correct pin outs:
  charliePlexPin(pin);  
  //on:
  digitalWrite(charliePin,HIGH);
  delayMicroseconds(sp*freq);
  // off:
  digitalWrite(charliePin,LOW);
  delayMicroseconds(sp*(255-freq));
}



// charlieplexing sets correct pin outs and returns pin to spwm to:
void charliePlexPin(int myLed){
  switch(myLed){

    // 1
  case 1:
    pinMode(led[0], OUTPUT);
    pinMode(led[1], OUTPUT);
    pinMode(led[2], INPUT);
    pinMode(led[3], INPUT);
    digitalWrite(led[0], LOW);
    charliePin = led[1];
    break;

    // 2
  case 2:
    pinMode(led[0], OUTPUT);
    pinMode(led[1], INPUT);
    pinMode(led[2], OUTPUT);
    pinMode(led[3], INPUT);
    digitalWrite(led[0], LOW);
    charliePin = led[2];
    break;

    // 3
  case 3:
    pinMode(led[0], OUTPUT);
    pinMode(led[1], INPUT);
    pinMode(led[2], INPUT);
    pinMode(led[3], OUTPUT);
    digitalWrite(led[0], LOW);
    charliePin = led[3];
    break;

    // 4
  case 4:
    pinMode(led[0], OUTPUT);
    pinMode(led[1], OUTPUT);
    pinMode(led[2], INPUT);
    pinMode(led[3], INPUT);
    digitalWrite(led[1], LOW);
    charliePin = led[0];
    break;

    // 5
  case 5:
    pinMode(led[0], OUTPUT);
    pinMode(led[1], INPUT);
    pinMode(led[2], OUTPUT);
    pinMode(led[3], INPUT);
    digitalWrite(led[1], LOW);
    charliePin = led[2];
    break;

    // 6
  case 6:
    pinMode(led[0], INPUT);
    pinMode(led[1], OUTPUT);
    pinMode(led[2], INPUT);
    pinMode(led[3], OUTPUT);
    digitalWrite(led[1], LOW);
    charliePin = led[3];
    break;

    // 7
  case 7:
    pinMode(led[0], OUTPUT);
    pinMode(led[1], INPUT);
    pinMode(led[2], OUTPUT);
    pinMode(led[3], INPUT);
    digitalWrite(led[2], LOW);
    charliePin = led[0];
    break;

    // 8
  case 8:
    pinMode(led[0], INPUT);
    pinMode(led[1], OUTPUT);
    pinMode(led[2], OUTPUT);
    pinMode(led[3], INPUT);
    digitalWrite(led[2], LOW);
    charliePin = led[1];
    break;

    // 9
  case 9:
    pinMode(led[0], INPUT);
    pinMode(led[1], INPUT);
    pinMode(led[2], OUTPUT);
    pinMode(led[3], OUTPUT);
    digitalWrite(led[2], LOW);
    charliePin = led[3];
    break;

    // 10
  case 10:
    pinMode(led[0], OUTPUT);
    pinMode(led[1], INPUT);
    pinMode(led[2], INPUT);
    pinMode(led[3], OUTPUT);
    digitalWrite(led[3], LOW);
    charliePin = led[0];
    break;

    // 11
  case 11:
    pinMode(led[0], INPUT);
    pinMode(led[1], OUTPUT);
    pinMode(led[2], INPUT);
    pinMode(led[3], OUTPUT);
    digitalWrite(led[3], LOW);
    charliePin = led[1];
    break;

    // 12
  case 12:
    pinMode(led[0], INPUT);
    pinMode(led[1], INPUT);
    pinMode(led[2], OUTPUT);
    pinMode(led[3], OUTPUT);
    digitalWrite(led[3], LOW);
    charliePin = led[2];
    break;
  }
}



















