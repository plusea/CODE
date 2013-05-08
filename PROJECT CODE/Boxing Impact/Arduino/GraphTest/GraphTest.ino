

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
}

void loop() {
  // send the value of analog input 0:
  Serial.print(analogRead(A0));
  Serial.print(",");
  Serial.print(analogRead(A0));
  Serial.println();
  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(10);
}

