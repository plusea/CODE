// software serial example for ATtiny!

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 2); // RX, TX
int calibration4 = 0;
int previous4;
int calibration3 = 0;
int previous3;
int calibration2 = 0;
int previous2;
int calibration1 = 0;
int previous1;



void setup()
{
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("starting...");

  // CAPACITIVE CALLIBRATION
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

  // calibrate pin 2:
  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration2 += chargeTime(PB2);
    delay(20);
  }
  calibration2 = (calibration2 + 4) / 8;

  // calibrate pin 1:
  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration1 += chargeTime(PB1);
    delay(20);
  }
  calibration1 = (calibration1 + 4) / 8;
}




void loop() // run over and over
{
  capSensing();
} 




