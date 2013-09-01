/*
  Some Noise!
  Generate noise using DigitalWrite and some delay, and some more stuff...
 
  This example code is for educational purpose and it is in the public domain.
*/
 
int led = 9;              // Pin 9 has an LED connected
int spk = 3;              // Pin 3 has a speaker connected


void setup() {                
  // initialize the digital pins as outputs
  pinMode(led, OUTPUT);
  pinMode(spk, OUTPUT);  
}


void loop() {
  // the raw way
  digitalWrite(led, HIGH);     // turn the LED on (HIGH is the voltage level)
  digitalWrite(spk, HIGH);     // turn the speaker on (HIGH is the voltage level)
  delayMicroseconds(100);      // wait
  
  digitalWrite(led, LOW);      // turn the LED off by making the voltage LOW
  digitalWrite(spk, LOW);      // turn the speaker off by making the voltage LOW
  delay(3);                    // wait
  
  // let's do it the right way
  //  analogWrite(led, 255);
  //  tone(spk, 440);
  
  // let's try to find some correlation
  //  int k = 0;
  //  analogWrite(led, k);
  //  tone(spk, map(k, 0, 1023, 100, 5000));
}
