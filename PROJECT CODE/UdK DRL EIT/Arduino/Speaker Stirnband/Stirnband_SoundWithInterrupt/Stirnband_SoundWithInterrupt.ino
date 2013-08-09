int buttonPin = 4;         // the number of the input pin
int speakerPin = 3;

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
int counter;
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif



void setup()
{
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  pinMode(speakerPin, OUTPUT);
  sbi(GIMSK, PCIE); // turn on pin change interrupt   
  sbi(PCMSK, PCINT0); // which pins are affected by interrupt
  beep(speakerPin, 2000, 1000);
}



void loop() {

}




ISR(PCINT0_vect){
  counter++;
    if(counter == 0) playMelody0();
  if(counter == 1) playMelody1();
  if(counter >=3) counter=0;
}



void playMelody0(){
  beep(speakerPin, 1000, 500);
}



void playMelody1(){
  beep(speakerPin, 20000, 2000);
}



