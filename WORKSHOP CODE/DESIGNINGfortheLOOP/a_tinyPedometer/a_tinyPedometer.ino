//ATtiny code
//Reads analog (or digital) input from pin 4 and every time the input goes bellow a set threshold 
//it counts one and displays the increase in count either by activating up one of four LEDs (or transistors)
//or one of twelve charlieplexed LEDs

// SET THESE VALUES:
int option = 3; //options: 1,2 or 3!
int threshold = 500;
////////////////////
int maxCount;
boolean sensorTriggered = false;
int count = 0;
int sensorValue = 0;
int lastButtonState;
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
////////////////////////////////////////////////////////////////////////////////
void setup(){
  if(option == 1 || option == 2) maxCount = 4;
  if(option == 3) maxCount = 12;
  for (int pin=0;pin<4;pin++){
    pinMode(pin,OUTPUT);
    digitalWrite(pin, LOW);
  }
  pinMode(4,INPUT);
  digitalWrite(4, HIGH);  //internal pull-up
}
////////////////////////////////////////////////////////////////////////////////
void loop(){
  //readSensor();
  testDigits();
}
void testDigits(){
    if(option == 1 || option == 2) fourLoop();
    if(option == 3) charlieLoop();
}
////////////////////////////////////////////////////////////////////////////////
void readSensor(){
  sensorValue = analogRead(2);  //pin4!
  delay(100);
  if(sensorValue < threshold && sensorTriggered == false) {
    sensorTriggered = true;
    count++;
    if(count > maxCount) count = 0;
    if(option == 1 || option == 2) fourLoop();
    if(option == 3) charlieLoop();
  }
  if(sensorValue > threshold) sensorTriggered = false;
}
////////////////////////////////////////////////////////////////////////////////
void fourLoop(){
  for (int i=0;i<count;i++) {
    digitalWrite(i, HIGH);
  }
  for (int i=count;i<maxCount;i++) {
    digitalWrite(i, LOW);
  }

}
////////////////////////////////////////////////////////////////////////////////
void charlieLoop(){
  for (int i=1;i<maxCount;i++) {
    charliePlexPin(i);
    delay(300);
  }
}
////////////////////////////////////////////////////////////////////////////////
void testLoop(){
  for (int c=1;c<13;c++) {
    charliePlexPin(c);
    delay(100);
  }
}
////////////////////////////////////////////////////////////////////////////////
void charliePlexPin(int myLed){
  switch(myLed){

    // 1
  case 1:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(2, HIGH);
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(0, LOW);
    digitalWrite(3, HIGH);
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(0, HIGH);
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(1, LOW);
    digitalWrite(3, HIGH);
    break;

    // 7
  case 7:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(0, LOW);
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
    break;

    // 9
  case 9:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    break;

    // 10
  case 10:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    digitalWrite(0, HIGH);
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    digitalWrite(1, HIGH);
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
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







