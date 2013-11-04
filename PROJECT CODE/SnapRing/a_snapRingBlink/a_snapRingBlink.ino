int timer = 100;
int ledPins[] = { 
  3,5,6,9,10,11,14,15,16 }; 
int ledPinsLength = 9;

void setup() {
  for (int thisPin = 0; thisPin < ledPinsLength; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);      
  }
}

void loop() {
  myOnOff();
  myFade1();
  myFade2();
  myBlink();

}

void myOnOff(){
  for(int thisPin=0; thisPin<ledPinsLength; thisPin++) digitalWrite(ledPins[thisPin], HIGH);
  delay(1000);
  for(int thisPin=0; thisPin<ledPinsLength; thisPin++) digitalWrite(ledPins[thisPin], LOW);
  delay(1000);
}



void myFade2(){

  for(int thisPin=0; thisPin<ledPinsLength; thisPin++) {
    for(int i=1;i<245;i++){
      spwm(ledPins[thisPin], i, 10);   
    }
    for(int i=254;i>1;i--){
      spwm(ledPins[thisPin], i, 10);   
    }
  }

}




void myFade1(){

  for(int i=1;i<245;i++){
    for(int thisPin=0; thisPin<ledPinsLength; thisPin++) {
      spwm(ledPins[thisPin], i, 1);   
    }
  }
  for(int i=254;i>1;i--){
    for(int thisPin=0; thisPin<ledPinsLength; thisPin++) {
      spwm(ledPins[thisPin], i, 1);   
    }
  }

}





void spwm(int spin, int freq,int sp){

  //on
  digitalWrite(spin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(spin,LOW);
  delayMicroseconds(sp*(255-freq));


}







void myBlink(){
  for (int thisPin = 0; thisPin < ledPinsLength; thisPin++) { 
    // turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);   
    delay(timer);                  
    // turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);    

  }

  // loop from the highest pin to the lowest:
  for (int thisPin = ledPinsLength - 1; thisPin >= 0; thisPin--) { 
    // turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    // turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);
  }
}







