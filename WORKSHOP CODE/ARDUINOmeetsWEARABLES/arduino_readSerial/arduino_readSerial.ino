void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0 and 1:
  int sensorValue1 = analogRead(A5);
  int sensorValue2 = analogRead(A1);
  // print out the value you read:
  Serial.print(sensorValue1);
  Serial.print(",");
  Serial.print(sensorValue2);
  Serial.print(",");
  Serial.println();
  
  delay(1);        // delay in between reads for stability
}
