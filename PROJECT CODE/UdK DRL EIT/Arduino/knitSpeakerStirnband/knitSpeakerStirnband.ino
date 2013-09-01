// code for knit speaker stirnband

int speakerL = 4;
int speakerR = 0;
int sensorL = 3; //adc3, digdital3
int sensorR = 1; //adc1, digital2
int sensorValueL;
int sensorValueR;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(speakerL, OUTPUT);     
  pinMode(speakerR, OUTPUT); 
  pinMode(3, INPUT); 
  pinMode(3, INPUT); 
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
}

void loop() {
  sensorValueL = analogRead(sensorL);
  sensorValueR = analogRead(sensorR);
  play(speakerL, sensorValueL, 100);
  play(speakerR, sensorValueR, 100);
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

