// UdK DRL EIT
// code that plays melody

int speakerPin = 0;      // select the pin for the LED

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(speakerPin, OUTPUT); 
}

void loop() {
  play(speakerPin, 1000, 500);
  play(speakerPin, 2000, 500);
  play(speakerPin, 3000, 500);
  play(speakerPin, 4000, 500);
  play(speakerPin, 5000, 500);
  play(speakerPin, 6000, 500);
  play(speakerPin, 7000, 500);
  play(speakerPin, 8000, 500);
}

void play(unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) // the sound producing function
{
  int x;
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) {
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  }
} 

