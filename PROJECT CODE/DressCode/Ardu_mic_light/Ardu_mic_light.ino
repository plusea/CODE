// code for arduino to read analog values from a mic and
// translate these into light patterns
// charlieplexing possible for more lights

int value;
int previousValue;
#define sensitivity 5

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  digitalWrite(14, HIGH);
}

void loop() {

  value = analogRead(A0);
  Serial.println(value);
  
  if((abs(value - previousValue)) > 5*sensitivity)
  digitalWrite(5, HIGH);
  else digitalWrite(5, LOW);
  
  if((abs(value - previousValue)) > 4*sensitivity)
  digitalWrite(6, HIGH);
  else digitalWrite(6, LOW);
  
  if((abs(value - previousValue)) > 3*sensitivity)
  digitalWrite(7, HIGH);
  else digitalWrite(7, LOW);
  
  if((abs(value - previousValue)) > 2*sensitivity)
  digitalWrite(8, HIGH);
  else digitalWrite(8, LOW);
  
  if((abs(value - previousValue)) > 1*sensitivity)
  digitalWrite(9, HIGH);
  else digitalWrite(9, LOW);

  previousValue = value;
  delay(2);
}
