/*
  Control Sound + Light
  Control pitch and amount of light with an analog input: a potentiometer
 
  This example code is for educational purpose and it is in the public domain.
*/

int led = 9;              // Pin 9 has an LED connected
int spk = 3;              // Pin 3 has a speaker connected
int sensorPin = A0;       // Analog Pin 0 has a potentiometer connected
int sensorVal = 0;        // Variable to store values read from the potentiometer

void setup() {
  // initialize the digital pins as outputs
  pinMode(led, OUTPUT);
  pinMode(spk, OUTPUT);
}

void loop() {
  sensorVal = analogRead(sensorPin);                  // read value from potentiometer
  
  int ledVal = map(sensorVal, 0, 1023, 0, 255);       // map the value to a level of brightness
  analogWrite(led, ledVal);                           // light up the LED
  
  int spkVal = map(sensorVal, 0, 1023, 100, 5000);    // map the value to a frequency (in Hz)
  tone(spk, spkVal);                                  // play the tone
}
