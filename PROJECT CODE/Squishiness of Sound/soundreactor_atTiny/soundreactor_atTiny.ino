#define numTaps 16
char taps[numTaps];
int led[]={
  0,1,2,3};
int charliePin;



void setup() {
  //pinMode(speakerPin, OUTPUT);  
  for (int z=0;z<4;z++){
    pinMode(led[z],OUTPUT);
  } //for z

  pinMode(4,INPUT);
  //Serial.begin(9600);
}

char count = 0;

void loop() {
  char micValue = analogRead(1) >> 2;
  char level = updateMA(micValue);
  //myBeep(micValue);
  //printBar(level);
  //analogWrite(1, level >> 2);
  //printBar(micValue);
  //Serial.println(updateMA(micValue));
  //Serial.println(micValue);
  //delay(100);

  char pin = level/4;
  if(pin > 12) pin = 12;
  
  
  if(++count == 13) count = 0;
  pin = count;
  delay(1000);

  for(int i=1; i<=12; i++){
    if(i < pin) {
      charliePlexPin(i);
      digitalWrite(charliePin, HIGH);
    }
    else digitalWrite(pin, LOW);
  }
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

//void printBar(int value) {
//  for(int i = 0; i < (value >> 2); i++) {
//    Serial.print('=');
//  }
//  Serial.println('|');
//}





// charlieplexing sets correct pin outs and returns pin to spwm to:
void charliePlexPin(int myLed){
  switch(myLed){

    // 1
  case 1:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    charliePin = 1;
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    charliePin = 2;
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(0, LOW);
    charliePin = 3;
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    charliePin = 0;
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    charliePin = 2;
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(1, LOW);
    charliePin = 3;
    break;

    // 7
  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    charliePin = 0;
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    charliePin = 1;
    break;

    // 9
  case 9:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(2, LOW);
    charliePin = 3;
    break;

    // 10
  case 10:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 0;
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 1;
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    charliePin = 2;
    break;
  }
}


