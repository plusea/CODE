//ATtiny code
//Reads analog (or digital) input from pin 4 and every time the input goes bellow a set threshold 
//it counts one and displays the increase in count either by activating up one of four LEDs (or transistors)
//or one of twelve charlieplexed LEDs

// SET THESE VALUES:
int threshold = 500;
int maxCount = 7;
////////////////////
boolean sensorTriggered = false;
int count = 0;
int sensorValue = 0;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
////////////////////////////////////////////////////////////////////////////////
void setup(){
  for (int pin=0;pin<4;pin++){
    pinMode(pin,OUTPUT);
    digitalWrite(pin, LOW);
  }
  pinMode(4,INPUT);
  digitalWrite(4, HIGH);  //internal pull-up
}
////////////////////////////////////////////////////////////////////////////////
void loop(){
  testDigits();
}
void testDigits(){
  charlieLoop();
}
////////////////////////////////////////////////////////////////////////////////
void readSensor(){
  sensorValue = analogRead(2);  //pin4!
  delay(100);
  if(sensorValue < threshold && sensorTriggered == false) {
    sensorTriggered = true;
    count++;
    if(count > maxCount) count = 0;
    charlieLoop();
  }
  if(sensorValue > threshold) sensorTriggered = false;
}
////////////////////////////////////////////////////////////////////////////////
void charlieLoop(){
  count++;

  for (int i=0;i<1000;i++) {
    for (int c=0;c<count;c++) {
      charliePlexPin(c);
    }
  }
  delay(1000);
  if(count > maxCount) count = 0;
}
////////////////////////////////////////////////////////////////////////////////
void charliePlexPin(int myLed){
  switch(myLed){

  case 0:
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(1, INPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(0, HIGH);
    break;

  case 1:
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(1, INPUT);
    pinMode(0, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    break;

  case 2:
    pinMode(3, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(0, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(3, HIGH);
    break;

  case 3:
    pinMode(1, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
    break;

  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(0, HIGH);
    break;

  case 5:
    pinMode(2, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(2, HIGH);
    break;

  case 6:
    pinMode(2, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(0, INPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    break;
  }
}
////////////////////////////////////////////////////////////////////////////////
void spwm(int freq,int pin,int sp){
  // call charlieplexing to set correct pin outs:
  //on:
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);
  // off:
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));
}










