/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int led[]={
  0,1,2,3,0,1,2,3};
int numberLEDs = 4;
int delayTime = 12;
int testDelay = 250;


void setup(){
  for(int z=0;z<numberLEDs;z++) pinMode(led[z], OUTPUT);
  for(int z=0;z<numberLEDs;z++) digitalWrite(led[z], LOW);
  pinMode(4, INPUT);
}


void loop(){
  for (int i=0;i<12;i++)
  charliePlex(i+1);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
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
  delay(testDelay);
  break;
  }
}

void spwm(int freq,int spin,int sp){

  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm










