// software serial example for ATtiny!

// send and receive:
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0, 1); // RX, TX

// only send:
#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial(1);  // TX 


#define sensorPin 3
#define speakerPin 4
#define ledPin 0

int sensorValue = 0;
int previousSensorTone = 0;
int sensorTone = 0;
int probeThreshold = 950;
int probeLedThreshold = 100;

void setup()  
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, probe!");

  pinMode(ledPin, OUTPUT);  
  pinMode(speakerPin, OUTPUT);  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  // BEEP TEST:
  myTone(speakerPin, 1000, 500);
  delay(100);

  // LED TEST:
  for(int i=0; i<255; i++){
    analogWrite(ledPin, i);
    delay(1);
  }
    for(int i=255; i>0; i--){
    analogWrite(ledPin, i);
    delay(1);
  }
  digitalWrite(ledPin, LOW);
}

void loop() // run over and over
{
  sensorValue = analogRead(sensorPin);
  mySerial.println(sensorValue);
  //delay(10); 
  //stretchPiano();
  //squeezeSound();
  probeNoise();
}

void probeNoise() {

  // MAKE NOISE TO REPRESENT RESISTANCE:
  if(sensorValue < probeThreshold) {
    myBeep(speakerPin, (1023-sensorValue)*6);
  }

  // ONLY TURN ON LED IF VERY CONDUCTIVE:
  if(sensorValue < probeLedThreshold) analogWrite(ledPin, 30);
  else digitalWrite(ledPin, LOW);

}






void squeezeSound() {
  if(sensorValue < probeThreshold) myBeep(speakerPin, (1023-sensorValue)*4);
}


void stretchPlay() {
  if(sensorValue > 400) myBeep(speakerPin, 2000);
}



void stretchPiano() {

  if(sensorValue < probeThreshold) {
    int sensorRange = 1023 - (1023-probeThreshold);
    int toneRange = sensorRange/8;

    sensorValue = 1023 - sensorValue;

    if(sensorValue > 100 && sensorValue < toneRange*1) sensorTone = 1;
    if(sensorValue > toneRange*1 && sensorValue < toneRange*2) sensorTone = 2;
    if(sensorValue > toneRange*2 && sensorValue < toneRange*3) sensorTone = 3; 
    if(sensorValue > toneRange*3 && sensorValue < toneRange*4) sensorTone = 4; 
    if(sensorValue > toneRange*4 && sensorValue < toneRange*5) sensorTone = 5; 
    if(sensorValue > toneRange*5 && sensorValue < toneRange*6) sensorTone = 6; 
    if(sensorValue > toneRange*6 && sensorValue < toneRange*7) sensorTone = 7; 
    if(sensorValue > toneRange*7) sensorTone = 8; 

    if(sensorTone != previousSensorTone){
      previousSensorTone = sensorTone;
      if(sensorTone == 1) myTone(speakerPin, 2093, 500);
      if(sensorTone == 2) myTone(speakerPin, 2349, 500);
      if(sensorTone == 3) myTone(speakerPin, 2637, 500);
      if(sensorTone == 4) myTone(speakerPin, 2793, 500);
      if(sensorTone == 5) myTone(speakerPin, 3136, 500);
      if(sensorTone == 6) myTone(speakerPin, 3520, 500);
      if(sensorTone == 7) myTone(speakerPin, 3951, 500);
      if(sensorTone == 8) myTone(speakerPin, 4186, 500);
    }
  }
}

void bendPiano() {
  if(sensorValue < 100 && sensorValue > 90) myBeep(speakerPin, 2093);
  if(sensorValue < 90 && sensorValue > 80) myBeep(speakerPin, 2349);
  if(sensorValue < 80 && sensorValue > 70) myBeep(speakerPin, 2637);
  if(sensorValue < 70 && sensorValue > 60) myBeep(speakerPin, 2793);
  if(sensorValue < 60 && sensorValue > 50) myBeep(speakerPin, 3136);
  if(sensorValue < 50 && sensorValue > 40) myBeep(speakerPin, 3520);
  if(sensorValue < 40 && sensorValue > 30) myBeep(speakerPin, 3951);
  if(sensorValue < 30 && sensorValue > 20) myBeep(speakerPin, 4186);
  if(sensorValue < 20) myBeep(speakerPin, 2093);
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



