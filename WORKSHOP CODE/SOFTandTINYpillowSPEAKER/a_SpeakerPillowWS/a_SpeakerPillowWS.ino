// code for ATtiny
// reads digital value and plays melody when triggered
// reads analog value and maps the value directly to a frequency



#define speakerPin 0
#define buttonPin 3
#define sensorPin 4
int sensorValue = 0;
int buttonValue = 0;



void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
}



void loop() {
  sensorValue = analogRead(2);
  if(sensorValue < 900) makeNoise(speakerPin, sensorValue*3);

  buttonValue = digitalRead(3);
  if(buttonValue == 0) playMelody(speakerPin);
  else noTone();
}



void makeNoise(unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) { 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 


void playPiano(unsigned char pin, int frequencyInHertz) {
  makeNoise(speakerPin, 2093, 100);
  delay(10);
  makeNoise(speakerPin, 2349, 100);
  delay(10);
  makeNoise(speakerPin, 2637, 100);
  delay(10);
  makeNoise(speakerPin, 2793, 100);
  delay(10);
  makeNoise(speakerPin, 3136, 100);
  delay(10);
  makeNoise(speakerPin, 3520, 100);
  delay(10);
  makeNoise(speakerPin, 3951, 100);
  delay(10);
  makeNoise(speakerPin, 4186, 100);
  delay(10);
}






