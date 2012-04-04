/*
2x2 presure sensor matrix code, 
 where each row/column is connected to an individual analog pin
 >> github plusea
 */

int rowPin1 = A2;
int rowPin2 = A3;
int colPin1 = 10;
int colPin2 = 11;
int sensorValues[] = {
  0,0,0,0};

void setup() {
  pinMode(rowPin1, INPUT);  
  pinMode(rowPin2, INPUT); 
  digitalWrite(16, HIGH); 
  digitalWrite(17, HIGH);
  pinMode(colPin1, OUTPUT);  
  pinMode(colPin2, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(colPin1, HIGH);
  digitalWrite(colPin2, LOW);
  sensorValues[0] = analogRead(rowPin1);
  sensorValues[1] = analogRead(rowPin2);
  delay(10);
  digitalWrite(colPin1, LOW);
  digitalWrite(colPin2, HIGH);
  sensorValues[2] = analogRead(rowPin1);
  sensorValues[3] = analogRead(rowPin2);
  delay(10);
  Serial.print(sensorValues[0]);
  Serial.print(',');
  Serial.print(sensorValues[1]);
  Serial.print(',');
  Serial.print(sensorValues[2]);
  Serial.print(',');
  Serial.print(sensorValues[3]);
  Serial.println();
}





