// code for ATtiny45 or 85

int speakerPin = 0;
int sensorPin = 3; // digital Pin 3 = ADC 3
int sensorValue = 0;

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  if(sensorValue < 700) playMelody(speakerPin);
  //if(sensorValue < 900) makeNoise(speakerPin, sensorValue*3, 100);
}

void makeNoise(unsigned char pin, int frequencyInHertz, long timeInMilliseconds) { 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(pin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(pin,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 

void playMelody(unsigned char pin) {
  makeNoise(pin, 1000, 300);
  delay(10);  
  makeNoise(pin, 2000, 600);
  delay(100);  
  makeNoise(pin, 3000, 900);
  delay(1000); 
}











