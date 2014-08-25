// code for hahnentritt stulpe by hannah
// runs on attiny85 or 45 (85v and 45v are low power versions)
// reads two analog inputs from knit sensors, and then executes one of the following actions:
// - blinks LED and sounds speaker if are thresholds are surpassed
// - sends sensor data over serial port


///////// CIRCUIT DIAGRAM /////////
//            _______
//      RST --|°    |-- VCC
// BOTsen/3 --|     |-- 2/ADC1/TOPsen/SCK
//  SPEAK/4 --|     |-- 1/TX/MISO
//      GND --|     |-- 0/LED/MOSI
//            _______
////////////////////////////////////


#include <SoftwareSerial.h>
//SoftwareSerial bluetooth(0,1); // RX, TX

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial bluetooth (1);  // TX 

int speakerPin = 4;
int ledPin = 0;
int sensor1BottomPin = 2; //ADC1
int sensor2TopPin = 3; //ADC3

//// variables to be changed: /////
int thresholdTOP = 400;  // yellow(1) = 100 // orange(2) = 300
int thresholdBOTTOM = 100;  // yellow(1) = 400 // orange(2) = 350
int triggerTime = 200; // NOT in millis() but it count cycles!
//////////////////////////////////

boolean isOverThreshold = false;
int timeCount;
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
int stateValue = 0; // 0 = nothing triggered, 1 = top sensor triggered, 2 = bottom sensor triggered, 3 = both, 4 = alarm sound

//////////////////////////////////
//////////////////////////////////
void setup() {
  bluetooth.begin(9600);   // set the baudrate to 9600, 115200 can be too fast at times for SoftSerial to relay the data reliably
  bluetooth.println("starting...");
  pinMode(speakerPin, OUTPUT);
  playNote(speakerPin, 1000, 500); // test speaker
  digitalWrite(speakerPin, LOW);  // turn speaker off
  pinMode(ledPin, OUTPUT);
  testBlinkLED();
  digitalWrite(ledPin, HIGH);  // turn LED off
  pinMode(2, INPUT); //ADC1
  pinMode(3, INPUT); //ADC3
  //digitalWrite(2, HIGH);  // turn on internal pull-up resistor
  //digitalWrite(3, HIGH);  // turn on internal pull-up resistor
}

//////////////////////////////////
//////////////////////////////////
void loop() {
  int sensorValue1Bottom = analogRead(1);
  int sensorValue2Top = analogRead(3);
  bluetooth.print(sensorValue2Top);
  bluetooth.print(",");
  bluetooth.print(sensorValue1Bottom);
  bluetooth.print(",");
  bluetooth.println(stateValue);
  delay(10);

  // if just TOP sensor triggered:
  if(sensorValue1Bottom > thresholdBOTTOM && sensorValue2Top < thresholdTOP) {
    stateValue = 1;
    blinkLED(500);  // blink slow
  }
    // if just BOTTOM sensor triggered:
  else if(sensorValue1Bottom < thresholdBOTTOM && sensorValue2Top > thresholdTOP) {
    stateValue = 2;
    blinkLED(200);  // blink fast
  }
  // if BOTH sensors triggered:
  else if(sensorValue1Bottom < thresholdBOTTOM && sensorValue2Top < thresholdTOP) {
    stateValue = 3;
    digitalWrite(ledPin, LOW); // turn LED on
    timeCount++; // keep track of activation time
    //bluetooth.println(timeCount);
    if(timeCount > triggerTime) {
      stateValue = 4;
      playNote(speakerPin, 1000, 500);
    }
  }
  else {          
    digitalWrite(ledPin, HIGH); // turn LED off
    stateValue = 0;
    timeCount=0;
  }
}

//////////////////////////////////
//////////////////////////////////
void blinkLED (int rate){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > rate) {
    previousMillis = currentMillis;  
    if (ledState == LOW) ledState = HIGH;
    else ledState = LOW;
    digitalWrite(ledPin, ledState);
  }
}

//////////////////////////////////
//////////////////////////////////
void playNote (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{	 
  int x;	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++)	 
  {	 
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  }	 
}

//////////////////////////////////
//////////////////////////////////
void testBlinkLED(){
  // fade on:
  for(int i = 255; i>0; i--){
    analogWrite(ledPin,i);
    delay(1);
  }
  // fade off:
  for(int i = 0; i<255; i++){
    analogWrite(ledPin,i);
    delay(1);
  }
}














