#define numTaps 16
char taps[numTaps];

void setup() {
  //pinMode(speakerPin, OUTPUT);  
  pinMode(2, INPUT);
  //digitalWrite(4, HIGH);  // sets pull-up for adc2
  //digitalWrite(14, HIGH);  // sets pull-up for adc2
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}
void loop() {
  char micValue = analogRead(A0) >> 2;
  char level = updateMA(micValue);
  //myBeep(micValue);
  //printBar(level);
  analogWrite(10, level >> 2);
  //printBar(micValue);
  //Serial.println(updateMA(micValue));
  //Serial.println(micValue);
  //delay(100);

}

char updateMA(char input) {
  int sum = 0;
  for(char i = 0; i < (numTaps - 1); i++) {  // shift array values along
    taps[i] = taps[i+1];
  }
  taps[numTaps - 1] = input;  // add latest value to array
  for(char i = 0; i < numTaps; i++) {  // shift array values along
    sum += taps[i];
  }
  return sum / numTaps;
}

void printBar(int value) {
  for(int i = 0; i < (value >> 2); i++) {
    Serial.print('=');
  }
  Serial.println('|');
}
