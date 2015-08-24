// code for textiles sensor demos

#define sensorPin 3
#define speakerPin 0


int sensorValue = 0;
int previousSensorTone = 0;
int sensorTone = 0;
int stretchSensorThreshold = 50;



void setup() {
  pinMode(speakerPin, OUTPUT);  
  pinMode(sensorPin, INPUT);
  //digitalWrite(sensorPin, HIGH);

}



void loop() {
  sensorValue = analogRead(sensorPin);
  if(sensorValue > stretchSensorThreshold) myBeep(speakerPin, (1023-sensorValue)*6);
}



void myBeep (unsigned char speaker, int frequencyInHertz)     // the sound producing function
{ 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);

  digitalWrite(speaker,HIGH);
  delayMicroseconds(delayAmount);
  digitalWrite(speaker,LOW);
  delayMicroseconds(delayAmount);

} 



void myTone (unsigned char speaker, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{ 	 
  int x; 	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) 	 
  { 	 
    digitalWrite(speaker,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speaker,LOW);
    delayMicroseconds(delayAmount);
  } 	 
} 







