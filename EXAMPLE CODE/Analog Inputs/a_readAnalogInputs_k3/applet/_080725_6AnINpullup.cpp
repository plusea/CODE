// www.plusea.at
// reads analog input from the five inputs from your arduino board 
// and sends it out via serial




// variables for input pins and
  #include "WProgram.h"
void setup();
void loop();
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
    Serial.print(10, BYTE); //end signal
	
    Serial.print(2, BYTE);
    Serial.print(value1);
    Serial.print(10, BYTE);
    
    Serial.print(3, BYTE);
    Serial.print(value2);
    Serial.print(10, BYTE);
    
    Serial.print(4, BYTE);
    Serial.print(value3);
    Serial.print(10, BYTE);
    
    Serial.print(5, BYTE);
    Serial.print(value4);
    Serial.print(10, BYTE);
    
    Serial.print(6, BYTE);
    Serial.print(value5);
    Serial.print(10, BYTE);

// wait for a bit to not overload the port
  delay(100);
}// end loop



int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

