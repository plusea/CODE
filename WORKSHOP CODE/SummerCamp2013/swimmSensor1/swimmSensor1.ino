// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
int swimmSensor1; 
//int swimmSensor2; 
Servo myservo;
int pos = 0;  

void setup() 
{ 
  pinMode(A2, INPUT_PULLUP);
  // pinMode(A3, INPUT_PULLUP);
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
} 


void loop() 
{ 
  swimmSensor1 = analogRead(A2);
  // swimmSensor2 = analogRead(A3);
  if(swimmSensor1 < 500) myservo.write(45);
  if(swimmSensor2 < 500) {

    //myservo.write(0);
    digitalWrite(6, HIGH);
  }
  else digitalWrite(6, LOW);


} 




