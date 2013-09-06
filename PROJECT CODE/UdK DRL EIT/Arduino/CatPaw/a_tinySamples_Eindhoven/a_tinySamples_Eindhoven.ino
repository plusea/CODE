// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX
int inByte = 'x';
int previousByte;
int calibration4 = 0;
int previous4;
int calibration3 = 0;
int previous3;

void setup()
{ 
  if(inByte == 'x'){
    mySerial.begin(9600);
    mySerial.println("Starting...");
  }
  // THERMOCHROMIC
  if(inByte == 't'){
    mySerial.println("Setup T");
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
  }
  /*
  // CAPACITIVE SENSING
  if(inByte == 'c'){
    mySerial.println("Setup C");
    // calibrate pin 4:
    delay(100);
    for (int i = 0; i < 8; i++) {
      calibration4 += chargeTime(PB4);
      delay(20);
    }
    calibration4 = (calibration4 + 4) / 8;
    // calibrate pin 3:
    delay(100);
    for (int i = 0; i < 8; i++) {
      calibration3 += chargeTime(PB3);
      delay(20);
    }
    calibration3 = (calibration3 + 4) / 8;
  }
  */
  // GRAPH
  if(inByte == 'g'){
    mySerial.println("Setup G");
    pinMode(2, INPUT);
    digitalWrite(2, HIGH);
    pinMode(3, INPUT);
    digitalWrite(3, HIGH);
    pinMode(4, INPUT);
    digitalWrite(4, HIGH);
  }
  
    // PLAY
  if(inByte == 'p'){
    mySerial.println("Setup P");
    pinMode(2, OUTPUT);
  }
}

void loop() // run over and over
{
  if (mySerial.available())
    inByte = mySerial.read();
  if(inByte != previousByte) setup();

  previousByte = inByte;

  // CAPACITIVE SENSING
  if(inByte == 'c'){
  //capSensing();
  }
  // GRAPH
 if(inByte == 'g'){
  graph();
}

  // SOUND
 if(inByte == 'p'){
  play();
}
} 





