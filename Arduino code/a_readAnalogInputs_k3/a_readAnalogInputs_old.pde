/*
Code based on “Arduino meets Processing” Potentiometer example
>> http://webzone.k3.mah.se/projects/arduino-workshop/projects/arduino_meets_processing/instructions/poti.html

Reads 4 analog inputs and visualizes them by drawing a 2x2 grid,
using grayscale shading of each square to represent sensor value.
>> http://www.kobakant.at/DIY/?cat=347
*/

// variables for input pins
  int analogInput0 = 0;
  int analogInput1 = 1;
  int analogInput2 = 2;
  int analogInput3 = 3;
  int analogInput4 = 4;
  int analogInput5 = 5;
  
// variable to store the value 
  int value0 = 0; 
  int value1 = 0; 
  int value2 = 0; 
  int value3 = 0;
  int value4 = 0;
  int value5 = 0; 

// variable used as breaker between sensor values  
  int breaker = 20;
 
 
void setup(){
// declaration of pin modes
  pinMode(analogInput0, INPUT);
  pinMode(analogInput1, INPUT);
  pinMode(analogInput2, INPUT);
  pinMode(analogInput3, INPUT);
  pinMode(analogInput4, INPUT);
  pinMode(analogInput5, INPUT);
  
// pullup resistors
  digitalWrite(14, HIGH); 
  digitalWrite(15, HIGH); 
  digitalWrite(16, HIGH); 
  digitalWrite(17, HIGH); 
  digitalWrite(18, HIGH); 
  digitalWrite(19, HIGH); 
  
// begin sending over serial port
  beginSerial(9600);
}// end setup





void loop(){
// read the value on analog input
  value0 = analogRead(analogInput0);
  value1 = analogRead(analogInput1);
  value2 = analogRead(analogInput2);
  value3 = analogRead(analogInput3);
  value4 = analogRead(analogInput4);
  value5 = analogRead(analogInput5);

// print out value over the serial port
    Serial.print(1, BYTE); //prefix
    Serial.print(value0);
    Serial.print(breaker, BYTE); //end signal
	
    Serial.print(2, BYTE);
    Serial.print(value1);
    Serial.print(breaker, BYTE);
    
    Serial.print(3, BYTE);
    Serial.print(value2);
    Serial.print(breaker, BYTE);
    
    Serial.print(4, BYTE);
    Serial.print(value3);
    Serial.print(breaker, BYTE);
    
    Serial.print(5, BYTE);
    Serial.print(value4);
    Serial.print(breaker, BYTE);
    
    Serial.print(6, BYTE);
    Serial.print(value5);
    Serial.print(breaker, BYTE);

// wait for a bit to not overload the port
  delay(100);
}// end loop


