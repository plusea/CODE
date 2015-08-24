/*
 square of eeonyx fabric with contacts running from each corner
 switching contacts to be HIGH or LOW
 detecting location of ANALOG INPUT contact as position of voltage divider
 */

#define side1 2
#define side2 3
#define side3 4
#define side4 5
#define contact A0

void setup() {
  pinMode(contact, INPUT); 
  pinMode(side1, OUTPUT);  
  pinMode(side2, OUTPUT);  
  pinMode(side3, OUTPUT);  
  pinMode(side4, OUTPUT);  
  Serial.begin(9600);
}

void loop() {

  // SENSOR VALUE 1:
  digitalWrite(side1, LOW);
  digitalWrite(side2, HIGH);
  digitalWrite(side3, HIGH);
  digitalWrite(side4, HIGH);
  delay(10);
  int sensorValue1 = analogRead(contact);

  // SENSOR VALUE 2:
  digitalWrite(side2, LOW);
  digitalWrite(side3, HIGH);
  digitalWrite(side4, HIGH);
  digitalWrite(side1, HIGH);
  delay(10);
  int sensorValue2 = analogRead(contact);


  // SENSOR VALUE 3:
  digitalWrite(side3, LOW);
  digitalWrite(side2, HIGH);
  digitalWrite(side4, HIGH);
  digitalWrite(side1, HIGH);
  delay(10);
  int sensorValue3 = analogRead(contact);


  // SENSOR VALUE 2:
  digitalWrite(side4, LOW);
  digitalWrite(side3, HIGH);
  digitalWrite(side2, HIGH);  
  digitalWrite(side1, HIGH);
  delay(10);
  int sensorValue4 = analogRead(contact);

  Serial.print(sensorValue1);
  Serial.print(",");
  Serial.print(sensorValue2);
  Serial.print(",");
  Serial.print(sensorValue3);
  Serial.print(",");
  Serial.print(sensorValue4);
  Serial.println();
}










