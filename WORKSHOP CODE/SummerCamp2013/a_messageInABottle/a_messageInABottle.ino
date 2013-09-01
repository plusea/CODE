// code for ATtiny
// fades an RGB LED through diferent colours

#define messagePin 4
#define line 1000
#define dot 200
#define space 1000

void setup(){
  pinMode(messagePin, OUTPUT);
}

void loop(){
  digitalWrite(messagePin, HIGH);
  delay(dot);
  digitalWrite(messagePin, LOW);
  delay(dot);
  digitalWrite(messagePin, HIGH);
  delay(dot);
  digitalWrite(messagePin, LOW);
  delay(dot);
  digitalWrite(messagePin, HIGH);
  delay(dot);
  digitalWrite(messagePin, LOW);
  delay(dot);
  digitalWrite(messagePin, HIGH);
  delay(dot);
  digitalWrite(messagePin, LOW);
  delay(dot);
}





