// code for ATtiny to read analog values from a mic and
// translate these into light patterns
// charlieplexing possible for more lights

int value;
int previousValue;
#define sensitivity 200

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  digitalWrite(4, HIGH);
}

void loop() {
  value = analogRead(2);
  
  if((abs(value - previousValue)) > 5*sensitivity)
  digitalWrite(3, HIGH);
  else digitalWrite(3, LOW);
  
  if((abs(value - previousValue)) > 4*sensitivity)
  digitalWrite(2, HIGH);
  else digitalWrite(2, LOW);
  
  if((abs(value - previousValue)) > 3*sensitivity)
  digitalWrite(1, HIGH);
  else digitalWrite(1, LOW);
  
  if((abs(value - previousValue)) > 2*sensitivity)
  digitalWrite(0, HIGH);
  else digitalWrite(0, LOW);

  previousValue = value;
  delay(2);
}
