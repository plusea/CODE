// customizeable graph code:
// send number to set number of analog inputs (1-6)
// send Y to turn on internal pull-ups
// send N to turn off internal pull-ups

char inByte;
int numberInputs = 1;
boolean pullups = true;
int inputs[] = { 
  A0, A1, A2, A3, A4, A5 }; 
  
  
void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  for(int i=0; i<numberInputs; i++) {
    if(pullups) pinMode(inputs[i], INPUT_PULLUP);
    else pinMode(inputs[i], INPUT);
  }
}

void loop() {
  if (Serial.available()) {
    inByte = Serial.read();
    Serial.write(inByte);
    Serial.println();

    if(inByte == 'Y' || inByte == 'y') pullups = true;
    else if(inByte == 'N' || inByte == 'n') pullups = false;
    else if (inByte == '1') numberInputs = 1;
    else if (inByte == '2') numberInputs = 2;
    else if (inByte == '3') numberInputs = 3;
    else if (inByte == '4') numberInputs = 4;
    else if (inByte == '5') numberInputs = 5;
    else if (inByte == '6') numberInputs = 6;
    else Serial.println("not a valid comand");
    setup();  
}

  for(int i=0; i<numberInputs; i++) {
    Serial.print(analogRead(inputs[i]));
    if(i < numberInputs-1)Serial.print(",");
  }
  Serial.println();
}







