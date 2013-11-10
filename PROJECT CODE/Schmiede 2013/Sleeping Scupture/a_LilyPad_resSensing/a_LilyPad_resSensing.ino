void setup() {
  pinMode(A0, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));
  delay(2);
}
