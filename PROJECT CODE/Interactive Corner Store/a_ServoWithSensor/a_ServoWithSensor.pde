// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 

int potpin = A2;  // analog pin used to connect the potentiometer
int val;
int previousVal;

void setup() 

{ 
  digitalWrite(16, HIGH);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 

void loop() 
{ 

  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  Serial.println(val);

  if(potpin < 800){
    val = map(val, 0, 1023, 0, 90);     // scale it to use it with the servo (value between 0 and 180) 
    myservo.write(val);                  // sets the servo position according to the scaled value 
    delay(15);
    previousVal = val; 
   
    
  }
  else   myservo.write(0);
} 

