/*
Code based on Tom Igoe's Serial Graphing Sketch
>> http://processing.org/exhibition/features/igoe/

Reads analog inputs and sends them as a series of strings seperated with commas,
and carriage returns after each full set of sensor values.
 >> http://www.kobakant.at/DIY/?cat=347
*/

int numberOfSensors = 6;
int sensorPins [numberOfSensors] = {
  0, 1, 2, 3, 4, 5};  //Analog input pins 0-5
int pullupPins [numberOfSensors] = {
  14, 15, 16, 17, 18, 19};  //Digital names for analog input pins 0-5


void setup() {
for(int i = 0; i < numberOfSensors; i++)  // set analog pins as inputs, although this is also the default
    pinMode(sensorPins[i], INPUT);
for(int i = 0; i < numberOfSensors; i++)  // set internal pullup resistors for all analog pins in use
    digitalWrite(pullupPins[i], HIGH);
  Serial.begin(9600);
}


void loop() {
for (int count = 0; count < numberOfSensors; count++) {
    int sensorReading = analogRead(sensorPins[count]);    // read each sensor as deffined in sensorPins array
    Serial.print(sensorReading, DEC);    // print its value out as an ASCII numeric string
    if (count < numberOfSensors - 1) Serial.print(",");    // if this isn't the last sensor to read then print a comma after it
  }
  
  Serial.println();  // after all the sensors have been read print a newline and carriage return
  delay(10);  // delay by # milliseconds
}



