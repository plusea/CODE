/*
 square of eeonyx fabric with contacts running along each side
 switching contacts to be HIGH, LOW or INPUT (no pullup)
 to detect location of ANALOG INPUT contact
 >> http://howtogetwhatyouwant.at/
 */

#define side1 2  // yellow
#define side2 3  // orange
#define side3 4  // green
#define side4 5  // blue
#define contact A0

void setup() {
  pinMode(contact, INPUT); 
  Serial.begin(9600);
}

void loop() {
  // READ X-direction:
  pinMode(side1, OUTPUT);  
  digitalWrite(side1, LOW);
  pinMode(side3, OUTPUT);  
  digitalWrite(side3, HIGH);
  pinMode(side2, INPUT);  
  pinMode(side4, INPUT);  
  delay(10);
  int sensorValueX = analogRead(contact);

  // READ Y-direction:
  pinMode(side4, OUTPUT);  
  digitalWrite(side4, LOW);
  pinMode(side2, OUTPUT);  
  digitalWrite(side2, HIGH);
  pinMode(side1, INPUT);  
  pinMode(side3, INPUT);  
  delay(10);
  int sensorValueY = analogRead(contact);

  Serial.print(sensorValueX);
  Serial.print(",");
  Serial.print(sensorValueY);
  Serial.println();
}







