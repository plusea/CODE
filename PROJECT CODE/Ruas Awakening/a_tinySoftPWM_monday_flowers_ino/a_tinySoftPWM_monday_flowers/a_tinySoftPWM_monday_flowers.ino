/*Software PWM on Attiny85
Ernst Christensen 16.okt. 2011
copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
*/

int led[]={
  0,1,2,3};
int randomPin[]={
  1,2,3,4,5,6,7,8,9,10,11,12,6,5,7,4,8,3,9,2,10,2,3,4,5,6,7,8,9,10,11,12,6,5,7,4,8,3,9,2,10,1,11,12,9,7,5,3,1,2,4,6,8,10,11,12,3,2,5,8,6,5,9,12,3,4,5};
int maxBrightness=100;
int arousalValue=0;
int arousalStage = 0;
double lightNum=0;
int delayTime = 4;
int LEDcount;
int r = 0;
int y = 0;
int charliePin;
boolean buttonPressed = false;
int timer;
int arousalCount = 1000;


void setup(){
  for (int z=0;z<4;z++){
    pinMode(led[z],OUTPUT);
  } //for z

  pinMode(4,INPUT);
  // COMMENT IN FOR CAPE!!!:
  //digitalWrite(4, HIGH); // no pull-up, use slider pin to GND instead
}



void loop(){
  flowersLoop();
  //capeLoop();
  //testLoop();
}




// blink through all 12 LEDs:
void testLoop(){
  for (int i=1;i<13;i++) {
    for (int x=1;x<254;x++) spwm(x,i,3);
    for (int x=254;x>1;x--) spwm(x,i,3);
  }
}




void flowersLoop(){
  arousalValue = analogRead(2);
  r = randomPin[y];

  for (int x=1;x<254;x++) {
    if(arousalValue < 1000 && arousalValue > 900) spwm(x,r,15);
    if(arousalValue < 900 && arousalValue > 800) spwm(x,r,6);
    if(arousalValue < 800) spwm(x,r,delayTime);
    if(arousalValue < 700) spwm(x,r+1,delayTime);
    if(arousalValue < 600) spwm(x,r+2,delayTime);
    if(arousalValue < 400) spwm(x,r+3,delayTime);
    if(arousalValue < 200) spwm(x,r+4,delayTime);
    if(arousalValue < 100) spwm(x,r+5,delayTime);

  }

  for (int x=254;x>1;x--) {
    if(arousalValue < 1000 && arousalValue > 900) spwm(x,r,15);
    if(arousalValue < 900 && arousalValue > 800) spwm(x,r,6);
    if(arousalValue < 800) spwm(x,r,delayTime);
    if(arousalValue < 700) spwm(x,r+1,delayTime);
    if(arousalValue < 600) spwm(x,r+2,delayTime);
    if(arousalValue < 400) spwm(x,r+3,delayTime);
    if(arousalValue < 200) spwm(x,r+4,delayTime);
    if(arousalValue < 100) spwm(x,r+5,delayTime);
  }

  y++;
  if(y > 24) y = 0;
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
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    charliePin = 1;
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    charliePin = 2;
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(0, LOW);
    charliePin = 3;
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    charliePin = 0;
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    charliePin = 2;
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(1, LOW);
    charliePin = 3;
    break;

    // 7
  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    charliePin = 0;
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    charliePin = 1;
    break;

    // 9
  case 9:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(2, LOW);
    charliePin = 3;
    break;

    // 10
  case 10:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 0;
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 1;
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 2;
    break;
  }
}
