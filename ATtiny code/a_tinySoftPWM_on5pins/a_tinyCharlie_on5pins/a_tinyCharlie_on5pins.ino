/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int led[]={
  0,1,2,3,4};
int numberLEDs = 5;
int delayTime = 12;
int testDelay = 250;
int charliePin;

void setup(){
  for(int z=0;z<numberLEDs;z++) pinMode(led[z], OUTPUT);
  for(int z=0;z<numberLEDs;z++) digitalWrite(led[z], LOW);
}


void loop(){
  for (int i=0;i<20;i++) {
    charliePlex(i+1);
    digitalWrite(charliePin, HIGH);
    delay(100);
    digitalWrite(charliePin, LOW);
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
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 1;
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 2;
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 3;
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    charliePin = 0;
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    charliePin = 2;
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    charliePin = 3;
    break;

    // 7
  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    charliePin = 0;
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    charliePin = 1;
    break;

    // 9
  case 9:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
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
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    charliePin = 0;
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    charliePin = 1;
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    charliePin = 2;
    break;

    // 13
  case 13:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(0, LOW);
    charliePin = 4;
    break;

    // 14
  case 14:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 0;
    break;

    // 15
  case 15:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(1, LOW);
    charliePin = 4;
    break;


    // 16
  case 16:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 1;
    break;

    // 17
  case 17:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    charliePin = 4;
    break;

    // 18
  case 18:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 2;
    break;

    // 19
  case 19:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 4;
    break;

    // 20
  case 20:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 3;
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














