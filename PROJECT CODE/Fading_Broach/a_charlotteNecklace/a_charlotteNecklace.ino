/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int numberLEDs = 5;
int delayTime = 12;
int charliePin;

void setup(){
  for(int z=0;z<numberLEDs;z++) pinMode(z, OUTPUT);
  for(int z=0;z<numberLEDs;z++) digitalWrite(z, LOW);
}


void loop(){

  //single round
  for (int i=1;i<9;i++) {
    for (int x=1;x<254;x++) spwm(x,i,delayTime);
    for (int x=254;x>1;x--) spwm(x,i,delayTime);
  }

  //double round
  for (int i=1;i<5;i++) {
    for (int x=1;x<254;x++) {
      spwm(x,i,delayTime);
      spwm(x,i+4,delayTime);
    }
    for (int x=254;x>1;x--) {
      spwm(x,i,delayTime);
      spwm(x,i+4,delayTime);
    }
  }


  //3 round
  for (int i=1;i<6;i++) {
    for (int x=1;x<254;x++) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
      spwm(x,i+2,delayTime);
    }
    for (int x=254;x>1;x--) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
      spwm(x,i+2,delayTime);
    }
  }


  //4 round
  for (int i=1;i<5;i++) {
    for (int x=1;x<254;x++) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
      spwm(x,i+2,delayTime);
      spwm(x,i+3,delayTime);
      spwm(x,i+4,delayTime);
    }
    for (int x=254;x>1;x--) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
      spwm(x,i+2,delayTime);
      spwm(x,i+3,delayTime);
      spwm(x,i+4,delayTime);
    }
  }

  //3 round
  for (int i=1;i<6;i++) {
    for (int x=1;x<254;x++) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
      spwm(x,i+2,delayTime);
    }
    for (int x=254;x>1;x--) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
      spwm(x,i+2,delayTime);
    }
  }

  //double round
  for (int i=1;i<5;i++) {
    for (int x=1;x<254;x++) {
      spwm(x,i,delayTime);
      spwm(x,i+4,delayTime);
    }
    for (int x=254;x>1;x--) {
      spwm(x,i,delayTime);
      spwm(x,i+4,delayTime);
    }
  }

  //sparkle
  for (int h=1;h<20;h++) {
    for (int i=1;i<9;i++) {
      spwm(255,i,100);
    }
    for (int i=9;i>0;i--) {
      spwm(255,i,100);
    }
  }


}




void charliePlexPin(int myLed){
  switch(myLed){


  case 1:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    charliePin = 2;
    break;


  case 2:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    charliePin = 1;
    break;


  case 3:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    charliePin = 2;
    break;



  case 4:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    charliePin = 4;
    break;

  case 5:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    charliePin = 2;
    break;

  case 6:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    charliePin = 3;
    break;

    //  case 7:
    //    pinMode(0, INPUT);
    //    pinMode(1, INPUT);
    //    pinMode(2, OUTPUT);
    //    pinMode(3, INPUT);
    //    pinMode(4, INPUT);
    //    charliePin = 2;
    //    break;

  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 3;
    break;

    //  case 9:
    //    pinMode(0, INPUT);
    //    pinMode(1, OUTPUT);
    //    pinMode(2, INPUT);
    //    pinMode(3, INPUT);
    //    pinMode(4, INPUT);
    //    charliePin = 1;
    //    break;


  case 8:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    charliePin = 1;
    break;
    //
    //  case 11:
    //    pinMode(0, OUTPUT);
    //    pinMode(1, OUTPUT);
    //    pinMode(2, INPUT);
    //    pinMode(3, INPUT);
    //    pinMode(4, INPUT);
    //    digitalWrite(1, LOW);
    //    charliePin = 0;
    //    break;

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















