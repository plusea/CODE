// code for Uno
// reads the analog value and maps the value to a note (audible frequency)

#define speakerPin 8
#define sensorPin A0
int sensorValue = 0;

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  
  if(sensorValue < 900) playPiano(speakerPin, sensorValue*3);

//  if(sensorValue < 900 && sensorValue > 800) playPiano(speakerPin, 2093);
//  if(sensorValue < 800 && sensorValue > 700) playPiano(speakerPin, 2349);
//  if(sensorValue < 700 && sensorValue > 600) playPiano(speakerPin, 2637);
//  if(sensorValue < 600 && sensorValue > 500) playPiano(speakerPin, 2793);
//  if(sensorValue < 500 && sensorValue > 400) playPiano(speakerPin, 3136);
//  if(sensorValue < 400 && sensorValue > 300) playPiano(speakerPin, 3520);
//  if(sensorValue < 300 && sensorValue > 200) playPiano(speakerPin, 3951);
//  if(sensorValue < 200 && sensorValue > 100) playPiano(speakerPin, 4186);
}

void playPiano(unsigned char pin, int frequencyInHertz) {
  long delayAmount = (long)(1000000/frequencyInHertz);
  digitalWrite(speakerPin,HIGH);
  delayMicroseconds(delayAmount);
  digitalWrite(speakerPin,LOW);
  delayMicroseconds(delayAmount);
}



