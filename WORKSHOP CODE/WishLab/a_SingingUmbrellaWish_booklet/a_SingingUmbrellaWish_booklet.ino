// singing umbrella code //

#define speakerPin = 0;
#define sensorPin1 = 1; // ADC 1, digital Pin 2
#define sensorPin2 = 2; // ADC 2, digital Pin 4
#define sensorPin3 = 3; // ADC 3, digital Pin 3
#define rainThreshold = 900;

void setup() {  // this is the setup function and is only called once
  pinMode(speakerPin, OUTPUT);
  digitalWrite(2, HIGH); //set internal pull-up ADC 1
  digitalWrite(3, HIGH); //set internal pull-up ADC 4
  digitalWrite(4, HIGH); //set internal pull-up ADC 3
}

void loop() { // this is the loop function and is only called over and over again
  int sensorValue1 = analogRead(sensorPin1);  // read values coming from ADC 1
  int sensorValue2 = analogRead(sensorPin2);  // read values coming from ADC 2
  int sensorValue3 = analogRead(sensorPin3);  // read values coming from ADC 3
  if(sensorValue1 < rainThreshold) playNote(speakerPin, 760, 400);
  if(sensorValue2 < 900) makeNoise(speakerPin, 1200, 400);
  if(sensorValue3 < 900) makeNoise(speakerPin, 3600, 400);
}

// the playNote function plays the frequency to the speaker
void playNote(unsigned char pin, int frequencyInHertz, long timeInMilliseconds) { 	 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (int x=0;x<loopTime;x++) { 	 
    digitalWrite(pin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(pin,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 


