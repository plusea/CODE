#define numberOfSensors 16
int input [numberOfSensors];

void setup() {

  //digitalWrite(14, HIGH); //pullup0
  //digitalWrite(15, HIGH); //pullup1
  //digitalWrite(16, HIGH); //pullup2
  //digitalWrite(17, HIGH); //pullup3
  digitalWrite(18, HIGH); //pullup4
  //digitalWrite(19, HIGH); //pullup5

  Serial.begin(9600);
}



void loop() {

for (int count = 0; count < numberOfSensors; count++) {
    int sensorReading = analogRead(count);    // read each sensor
    Serial.print(sensorReading, DEC);    // print its value out as an ASCII numeric string
    if (count < numberOfSensors -1) Serial.print(",");    // if this isn't the last sensor to read then print a comma after it
  }
  
  // after all the sensors have been read print a newline and carriage return
  Serial.println();
  delay(100);
}



