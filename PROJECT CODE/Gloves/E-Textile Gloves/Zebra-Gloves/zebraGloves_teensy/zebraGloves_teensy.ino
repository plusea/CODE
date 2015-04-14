/*
Code to parse through 6 connections ar e-textile gloves
sets on strip to analog pin read
resistors are conencted to digital i/o pins
corresponding resistor pin is grounded as pull-down resisor
the rest are set to high-impedance (INPUT)
corresponding vcc strip is set to HIGH
analog value is red and sent over serial
*/

// Analog pins;
const int analogPins[6] = {
 A0, A1, A2, A3, A4, A5
};

// Analog pins digital names;
const int analogPinsDigital[6] = {
 21, 20, 19, 18, 17, 16
};

// Corresponding vcc pins;
const int vccPins[6] = {
 A1, A2, A3, A4, A5, A0
};


// Digital pins as pull-down resistors;
const int digitalPins[6] = {
 0, 1, 2, 3, 4, 5
};


// Analog values;
int sensorValue[5] = {
 0, 0, 0, 0, 0
};


void setup() {
 Serial.begin(19200);
}


void loop() {
 parseGloveManual();
}


void parseGloveManual() {

 // set all analog and digital pins to high-impedance (INPUT)
 for( int i=0; i<6; i++ ){
   pinMode(analogPins[i], INPUT);
   pinMode(digitalPins[i], INPUT);
 }

 // case1:
 pinMode(21, OUTPUT);
 digitalWrite(21, HIGH);
 pinMode(1, OUTPUT);
 digitalWrite(1, LOW);
 sensorValue[0] = analogRead(A1);

 // set all analog and digital pins to high-impedance (INPUT)
 for( int i=0; i<6; i++ ){
   pinMode(analogPins[i], INPUT);
   pinMode(digitalPins[i], INPUT);
 }

 // case2:
 pinMode(20, OUTPUT);
 digitalWrite(20, HIGH);
 pinMode(2, OUTPUT);
 digitalWrite(2, LOW);
 sensorValue[1] = analogRead(A2);

 // set all analog and digital pins to high-impedance (INPUT)
 for( int i=0; i<6; i++ ){
   pinMode(analogPins[i], INPUT);
   pinMode(digitalPins[i], INPUT);
 }

 // case3:
 pinMode(19, OUTPUT);
 digitalWrite(19, HIGH);
 pinMode(3, OUTPUT);
 digitalWrite(3, LOW);
 sensorValue[2] = analogRead(A3);

 // set all analog and digital pins to high-impedance (INPUT)
 for( int i=0; i<6; i++ ){
   pinMode(analogPins[i], INPUT);
   pinMode(digitalPins[i], INPUT);
 }

 // case4:
 pinMode(18, OUTPUT);
 digitalWrite(18, HIGH);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 sensorValue[3] = analogRead(A4);


 // set all analog and digital pins to high-impedance (INPUT)
 for( int i=0; i<6; i++ ){
   pinMode(analogPins[i], INPUT);
   pinMode(digitalPins[i], INPUT);
 }

 // case5:
 pinMode(17, OUTPUT);
 digitalWrite(17, HIGH);
 pinMode(5, OUTPUT);
 digitalWrite(5, LOW);
 sensorValue[4] = analogRead(A5);
}





void parseGloveLoop() {
 for( int i=0; i<5; i++ ){

   // first set all GND and ANALOG pins to floating:
   for( int f=0; f<6; f++ ){
     pinMode(digitalPins[f], INPUT);
     pinMode(analogPins[f], INPUT);
   }

   // then set current GND pin to LOW to connect pull-down resistor:
   pinMode(digitalPins[i], OUTPUT);
   digitalWrite(digitalPins[i], LOW);

   // then set current VCC pin to HIGH:
   //pinMode(vccPins[i], OUTPUT);
   digitalWrite(vccPins[i], HIGH);

   // then set current ANALOG INPUT pin to INPUT:
   pinMode(analogPins[i], INPUT);

   // read value of current sensor pin:
   sensorValue[i] = analogRead(analogPins[i]);

   // print value:
   Serial.print( sensorValue[i] ), Serial.print( "\t" );

 }
 Serial.println();
 delay(50);

}




