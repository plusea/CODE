boolean test = true;

void setup() {
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);
  Serial.begin(9600);

  if(test == true){
    for(int i=0; i<10; i++){

      Serial.print(i);
      Serial.print("\t");
      Serial.print("OPEN");
      delay(500);
      Serial.print(" 1 ");
      delay(500);
      Serial.print(" 2 ");
      delay(500);
      Serial.print(" 3:\t");
      delay(500);
      Serial.print(analogRead(A2));
      Serial.print("\t");
      Serial.println(analogRead(A3));
      delay(500);
      Serial.print(i);
      Serial.print("\t");
      Serial.print("FIST");
      delay(500);
      Serial.print(" 1 ");
      delay(500);
      Serial.print(" 2 ");
      delay(500);
      Serial.print(" 3:\t");
      delay(500);
      Serial.print(analogRead(A2));
      Serial.print("\t");
      Serial.println(analogRead(A3));
      delay(500);
    }
  }
}

void loop() {
  if(test == false){
    Serial.print(analogRead(A2));
    Serial.print("\t");
    Serial.println(analogRead(A3));
  }
}





