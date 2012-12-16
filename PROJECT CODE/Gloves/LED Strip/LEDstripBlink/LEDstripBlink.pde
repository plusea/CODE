int LEDs[] = {
  A0, A2, 6, A3, A1, A3};
int r = 3;
int g = 5;
int b = 6;

int d = 5;

void setup() {
  for(int i=0; i<8; i++) pinMode(LEDs[i], OUTPUT); 
  pinMode(9, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  digitalWrite(9, LOW);
}



void loop() {

  for(int i=0; i<255; i++){
    analogWrite(10, i);      
analogWrite(r, i);
  analogWrite(g, i*3);
analogWrite(b, i*5);
delay(d);
  }

  for(int i=255; i>0; i--){
    analogWrite(10, i);      
        analogWrite(r, i);
  analogWrite(g, i*3);
  analogWrite(b, i*5);
delay(d);
  }

 
  
 
}





