// customizeable graph code

int numberInputs = 6;
int inputs[] = { 
  A0, A1, A2, A3, A4, A5 }; 


void setup() {

  for(int i=0; i<numberInputs; i++) pinMode(inputs[i], INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  for(int i=0; i<numberInputs; i++) {
    Serial.print(analogRead(inputs[i]));
    if(i < numberInputs-1)Serial.print(",");
  }
  Serial.println();
}








