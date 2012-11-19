// code for ATtiny
// fades LEDs on all five pins on and off using software PWM
// softwarePWM function taken from :

#define fadeSpeed 20
void setup(){
  for(int pin=0;pin<5;pin++) pinMode(pin, OUTPUT);
}
void loop(){
  for(int pin=0;pin<5;pin++) {
    for(int fade=1;fade<254;fade++) {  //fade on
      softPWM(pin, fade, fadeSpeed);
    }
    for(int fade=254;fade>1;fade--) {  //fade off
      softPWM(pin, fade, fadeSpeed);
      }  
    }  
  }
  void softPWM(int pin, int freq, int sp) {  // software PWM function that fakes analog output
    digitalWrite(pin,HIGH);  //on
    delayMicroseconds(sp*freq);
    digitalWrite(pin,LOW);  //off
    delayMicroseconds(sp*(255-freq));
  }

