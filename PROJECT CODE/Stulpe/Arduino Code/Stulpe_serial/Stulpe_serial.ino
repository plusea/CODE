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
int threshold1 = 50;
int threshold2 = 300;
int triggerTime = 1000;
//////////////////////////////////

boolean isOverThreshold = false;
int timeCount;
int LEDstate = 0;

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


void loop() {
  int sensorValue1Bottom = analogRead(1);
  int sensorValue2Top = analogRead(3);
  bluetooth.print(sensorValue2Top);
  bluetooth.print(",");
  bluetooth.println(sensorValue1Bottom);
  delay(10);
  
  // if just BOTTOM sensor triggered:
  if(sensorValue1Bottom < threshold1 && sensorValue2Top > threshold2) blinkLED(200);
  // if just TOP sensor triggered:
  else if(sensorValue1Bottom > threshold1 && sensorValue2Top < threshold2) blinkLED(500);
  // if BOTH sensors triggered:
  else if(sensorValue1Bottom < threshold1 && sensorValue2Top < threshold2) {
    digitalWrite(ledPin, LOW); // turn on LED
    timeCount++; // take note of the activation time
  }
  else 
  
  if(sensorValue1Bottom >= threshold1 || sensorValue2Top >= threshold2) {                                   // if the values are under the threshold
    timeCount=0;
  }

  if(timeCount >= triggerTime) {            // if the activation time was more than 5 secs ago
    bluetooth.println("Ring Ring");         // ring the bell
    playNote(speakerPin, 1000, 500); 
    blinkLED(500);
  }
}

void blinkLED (int rate){
  if(millis() % rate == 0 && LEDstate == 0) LEDstate = 1;
  if(millis() % rate == 0 && LEDstate == 1) LEDstate = 0;
  digitalWrite(ledPin, LEDstate);
  
}

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











