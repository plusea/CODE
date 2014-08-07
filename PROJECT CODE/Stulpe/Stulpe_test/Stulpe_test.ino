// code for hahnentritt stulpe by hannah
// runs on attiny45
// blinks LED and sounds buzzer for testing

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(5, 0); // RX, TX

//#include <SendOnlySoftwareSerial.h>
//SendOnlySoftwareSerial mySerial (0);  // Tx pin 

int speakerPin = 4;
int ledPinGreen = 1;
int ledPinBlue = 0;


void setup() {
  // set the data rate for the SoftwareSerial port
  //mySerial.begin(57600);
  //mySerial.println("starting...");
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
  digitalWrite(ledPinGreen, HIGH);  //off
  digitalWrite(ledPinBlue, HIGH);  //off
}


void loop() {
  digitalWrite(ledPinGreen, LOW);  //on
  digitalWrite(ledPinBlue, HIGH);  //off
  delay(1000);
  digitalWrite(ledPinGreen, HIGH);  //off
  digitalWrite(ledPinBlue, LOW);  //on
  delay(1000);
  //turquoise:
  digitalWrite(ledPinGreen, LOW);
  digitalWrite(ledPinBlue, LOW);
  delay(1000);
  digitalWrite(ledPinGreen, HIGH);  //off
  digitalWrite(ledPinBlue, HIGH);  //off
  playNote(speakerPin, 1000, 1000); 
  delay(1000);

}



void playNote (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{	 
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












