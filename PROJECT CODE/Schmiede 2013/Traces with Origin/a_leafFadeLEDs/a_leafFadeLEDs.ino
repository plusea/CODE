/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int numberLEDs = 5;
int delayTime = 12;

void setup(){
  for(int z=0;z<numberLEDs;z++) pinMode(z, OUTPUT);
  for(int z=0;z<numberLEDs;z++) digitalWrite(z, LOW);
}


void loop(){

  //single round
  for (int i=0;i<numberLEDs;i++) {
    for (int x=1;x<254;x++) spwm(x,i,delayTime);
    for (int x=254;x>1;x--) spwm(x,i,delayTime);
  }

  //double round
  for (int i=0;i<numberLEDs;i++) {
    for (int x=1;x<254;x++) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
    }
    for (int x=254;x>1;x--) {
      spwm(x,i,delayTime);
      spwm(x,i+1,delayTime);
    }
  }


  //3 round
  for (int i=0;i<numberLEDs;i++) {
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
  for (int i=0;i<numberLEDs;i++) {
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
  for (int i=0;i<numberLEDs;i++) {
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
  for (int i=0;i<numberLEDs;i++) {
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
  for (int h=0;h<20;h++) {
    for (int i=0;i<numberLEDs;i++) {
      spwm(255,i,100);
    }
    for (int i=numberLEDs;i>0;i--) {
      spwm(255,i,100);
    }
  }
}







// software PWM
void spwm(int freq,int pin,int sp){
  // call charlieplexing to set correct pin outs:
  //on:
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);
  // off:
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));
}















