/*
  Pitch follower
 
 Plays a pitch that changes based on a changing analog input
 
 circuit:
 * 8-ohm speaker on digital pin 8
 * photoresistor on analog 0 to 5V
 * 4.7K resistor on analog 0 to ground
 
 created 21 Jan 2010
 modified 31 May 2012
 by Tom Igoe, with suggestion from Michael Flynn

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone2
 
 */


void setup() {
  pinMode(A2, INPUT_PULLUP);
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A2);
  // print the sensor reading so you know its range
  Serial.println(sensorReading);
  // map the analog input range (in this case, 400 - 1000 from the photoresistor)
  // to the output pitch range (120 - 1500Hz)
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  int thisPitch = map(sensorReading, 0, 900, 120, 1500);

  if(sensorReading < 900) tone(5, thisPitch, 10);
  else noTone(5);
  
  delay(1);        // delay in between reads for stability
}






