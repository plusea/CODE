
int led = 4;
int state;

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// the setup routine runs once when you press reset:
void setup() { 
  pinMode(led, OUTPUT); 
  pinMode(0, INPUT); 
  //digitalWrite(1, HIGH); // turn on internal pull-up resistor
  sbi(GIMSK, PCIE); // turn on pin change interrupt   
  sbi(PCMSK, PCINT0); // which pins are affected by interrupt
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, LOW);
  //digitalWrite(
  //digitalWrite(led, state);
}

ISR(PCINT0_vect){
  digitalWrite(led, HIGH);
  delay(1000);
  //if(state == 0) state = 1;
  //if(state == 1) state = 0;
}



