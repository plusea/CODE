

byte analogPins[] = { 
  A0, A1, A2, A3, A4, A5, A6, A7 };  

void setup() {
  for(int i=0;i<8;i++){
  pinMode(analogPins[i], INPUT_PULLUP);  
  }
  Serial.begin(9600);
}

void loop() {
  for(int i=0;i<8;i++){
  Serial.print(analogRead(analogPins[i]));    
  Serial.print("\t");
  }
  Serial.println();
}
