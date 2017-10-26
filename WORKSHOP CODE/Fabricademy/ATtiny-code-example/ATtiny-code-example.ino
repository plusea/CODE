/*
   CODE for the Fabricademy e-textile sensor swatch
   first built for the Fabricademy 2017
   Hannah Perner-Wilson and Mika Satomi, KOBAKANT
*/

#define sensorPin 3
#define speakerPin 2
#define ledPin 0

int sensorValue = 0;
int noiseFrequency = 0;
int ledBrightness = 0;

void setup()
{
  pinMode(sensorPin, INPUT); // use digital pin number here
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  sensorValue = analogRead(sensorPin); // use analog pin number here
  
  // MAKE SOUND:
  if(sensorValue < 900){
  noiseFrequency = map(sensorValue, 0, 1023, 100, 10000);
  noise (speakerPin, noiseFrequency);
  }

  // FADE LED:
  ledBrightness = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(ledPin, ledBrightness);
}


// MAKE SOUND ON THE ATTINY WITHOUT THE SOUND LIBRARY:
void noise (unsigned char noisePin, int frequencyInHertz) {
  long delayAmount = (long)(1000000 / frequencyInHertz);
    digitalWrite(noisePin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(noisePin, LOW);
    delayMicroseconds(delayAmount);
}
