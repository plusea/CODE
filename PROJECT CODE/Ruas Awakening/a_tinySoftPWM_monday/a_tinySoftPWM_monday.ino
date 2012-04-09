/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int led[]={
  0,1,2,3};
int randomPin[]={
  1,2,3,4,5,6,7,8,9,10,11,12,6,5,7,4,8,3,9,2,10,1,11,12,9,7,5,3,1,2,4,6,8,10,11,12};
int count=0;
int maxBrightness=100;
int arousalValue=0;
int button=0;
double dLay=20;
double lightNum=0;
int delayTime = 1;
int aV;
int LEDcount;
int r = 0;
int i = 0;
int charliePin;


void setup(){
  for (int z=0;z<4;z++){
    pinMode(led[z],OUTPUT);
  } //for z

  pinMode(4,INPUT);
  //digitalWrite(4, HIGH); // no pull-up, use slider pin to GND instead
}


void loop(){
  testLoop2();
  //testLoop();
}




void testLoop2(){
  arousalValue = analogRead(2);
  r = randomPin[i];
  
  for (int x=1;x<254;x++) {
    if(arousalValue < 200) spwm(x,r,delayTime);
    if(arousalValue < 400) spwm(x,r+1,delayTime);
    if(arousalValue < 600) spwm(x,r+2,delayTime);
    if(arousalValue < 800) spwm(x,r+3,delayTime);
    if(arousalValue < 1000) spwm(x,r+4,delayTime);

  }
  
  for (int x=254;x>1;x--) {
    if(arousalValue < 200) spwm(x,r,delayTime);
    if(arousalValue < 400) spwm(x,r+1,delayTime);
    if(arousalValue < 600) spwm(x,r+2,delayTime);
    if(arousalValue < 800) spwm(x,r+3,delayTime);
    if(arousalValue < 1000) spwm(x,r+4,delayTime);
  }
  
  i++;
  if(i > 24) i = 0;
}



void testLoop(){
  for (int i=1;i<13;i++) {
    charliePlex(i);
  }
}







void spwm(int freq,int pin,int sp){
  
  charliePlexPin(pin);
  
  //on
  digitalWrite(charliePin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(charliePin,LOW);
  delayMicroseconds(sp*(255-freq));
} //spwm






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


void charliePlex(int myLed){
  switch(myLed){
    // 1
  case 1:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    for (int x=1;x<254;x++) spwm(x,1,delayTime);
    for (int x=254;x>1;x--) spwm(x,1,delayTime);
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    for (int x=1;x<254;x++) spwm(x,2,delayTime);
    for (int x=254;x>1;x--) spwm(x,2,delayTime);
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(0, LOW);
    for (int x=1;x<254;x++) spwm(x,3,delayTime);
    for (int x=254;x>1;x--) spwm(x,3,delayTime);
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    for (int x=1;x<254;x++) spwm(x,0,delayTime);
    for (int x=254;x>1;x--) spwm(x,0,delayTime);
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    for (int x=1;x<254;x++) spwm(x,2,delayTime);
    for (int x=254;x>1;x--) spwm(x,2,delayTime);
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(1, LOW);
    for (int x=1;x<254;x++) spwm(x,3,delayTime);
    for (int x=254;x>1;x--) spwm(x,3,delayTime);
    break;

    // 7
  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    for (int x=1;x<254;x++) spwm(x,0,delayTime);
    for (int x=254;x>1;x--) spwm(x,0,delayTime);
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    for (int x=1;x<254;x++) spwm(x,1,delayTime);
    for (int x=254;x>1;x--) spwm(x,1,delayTime);
    break;

    // 9
  case 9:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(2, LOW);
    for (int x=1;x<254;x++) spwm(x,3,delayTime);
    for (int x=254;x>1;x--) spwm(x,3,delayTime);
    break;

    // 10
  case 10:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    for (int x=1;x<254;x++) spwm(x,0,delayTime);
    for (int x=254;x>1;x--) spwm(x,0,delayTime);
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    for (int x=1;x<254;x++) spwm(x,1,delayTime);
    for (int x=254;x>1;x--) spwm(x,1,delayTime);
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    for (int x=1;x<254;x++) spwm(x,2,delayTime);
    for (int x=254;x>1;x--) spwm(x,2,delayTime);
    break;
  }
}


void fLoop(){
  if (lightNum==0.0)  
    checkButton();

  if (button==0)
    return;

  //one light
  if (button==1){  
    if (int(lightNum)==0){
      doLED(0,2,20, 60);
    }
    checkButton();

    //two lights
    if (int(lightNum)==1){
      doLED(1,5,20, 120);
      doLED(0,3,20, 120);
      doLED(1,4,20, 120);
      doLED(2,3,40, 120);
      doLED(0,2,40, 120);
    }
    checkButton();

    // three lights:
    if (int(lightNum)==2) {
      doLED(0,2,10, 100);
      doLED(1,3,10, 100);
      doLED(0,4,10, 200);
      doLED(0,2,10, 100);
    }
    checkButton();

    if (int(lightNum)==3){
      doLED(0,3,1,150);
      doLED(3,4,1,200);
      doLED(1,2,1,150);
      doLED(2,3,1,100);
      doLED(0,2,1,200);
      doLED(3,4,1,150);
      doLED(0,1,1,100);
      doLED(3,4,5,150);
      doLED(1,2,1,200);
      doLED(4,5,1,100);

    }
    checkButton();

    if (maxBrightness>254)
      maxBrightness=254;

    if (lightNum>3)
      lightNum=3;

    if (dLay<1)
      dLay=1;

  }
}







void doLED(int ledStart,int ledEnd,int delayTime,int bright){

  for (int x=1;x<bright;x++){
    for (int y=ledStart;y<ledEnd;y++) spwm(x,led[y],delayTime);

    arousalValue = analogRead(2);
    if (arousalValue < 400 && arousalValue > 0 ){
      button=1;
      lightNum+=0.01;
      return;

      if (arousalValue < 100){
        button=-1;
      }
    }
    arousalValue=0;


  }
  for (int x=bright;x>1;x--){
    for (int y=ledStart;y<ledEnd;y++) spwm(x,led[y],delayTime);


    arousalValue = analogRead(2);
    if (arousalValue < 400 && arousalValue > 0 ){
      button = 1;
      lightNum += 0.01;
      return;
      if (arousalValue < 100){
        button = -1;
      }
    }
    arousalValue=0;          
  }
}






void checkButton(){
  arousalValue = analogRead(2);
  if (arousalValue < 400 && arousalValue > 0 ){
    button=1;
    lightNum+=0.01;
    if (arousalValue < 100){
      button=-1;
    }
  }
  arousalValue=0;
}








