// code for ATtiny
// reads the analog value and maps the value to a note (audible frequency)
// makeSound function modified from Leah Buechley’s sound example: http://web.media.mit.edu/~leah/LilyPad/07_sound.html

#define speakerPin 0
#define sensorPin 4
#define threshold 800
int sensorValue = 0;  //create a variable to store the incoming sensor value in

void setup() {
  pinMode(speakerPin, OUTPUT);  //initialize the speakerPin as an output
  pinMode(sensorPin, INPUT);  //initialize the sensorPin as in input by refering to it’s port number (PB4)
}

void loop() {
  sensorValue = analogRead(2);  //remember to refer to the ADC pin of the ATtiny when reading an analog input
  if(sensorValue < threshold) {  //if the incoming sensor value falls bellow the threshold, then do the following...
    makeSound(speakerPin, sensorValue*3);  //use the sensor value multiplied by three as the frequency
  }
}

void makeSound(unsigned char pin, int frequencyInHertz) {
  long delayAmount = (long)(1000000/frequencyInHertz);	 
  digitalWrite(speakerPin,HIGH);
  delayMicroseconds(delayAmount);
  digitalWrite(speakerPin,LOW);
  delayMicroseconds(delayAmount);
}
