/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 */

int led[]={
  0,1,2};
int numberPins = 3;
int numberCharlies = 6;
int charliePin;

void setup(){
  for(int z=0;z<numberPins;z++) pinMode(led[z], OUTPUT);
  for(int z=0;z<numberPins;z++) digitalWrite(led[z], LOW);
  
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
}


void loop(){
  for (int i=0;i<numberCharlies;i++) {
    charliePlex(i+1);
    digitalWrite(charliePin, HIGH);
    delay(50);
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
    digitalWrite(0, LOW);
    charliePin = 1;
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    digitalWrite(1, LOW);
    charliePin = 0;
    break;

    // 3
  case 3:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    digitalWrite(1, LOW);
    charliePin = 2;
    break;

    // 4
  case 4:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    charliePin = 1;
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(0, LOW);
    charliePin = 2;
    break;
    
        // 6
  case 6:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    charliePin = 0;
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














