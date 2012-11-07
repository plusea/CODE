/*
 This code uses a count instead of a delay function to do 
 two seperate instances of PWM on an ATtiny 45 microcontroller.
 
 One PWM creates a square wave frequency for a speaker to play,
 the hardware PWM slowly fades an LED on and off.
 
 We do this so that the delay() function called to control the 
 speed of the fading LED does not interfere with the speed of the frequency.
 */

// LED fade pins are fixed because of hardware PWM:
#define led1 0  // pin 5
#define led2 1  // pin 6

// DIFFERENT CIRCUITS, DIFFERENT PINS /////////////////////
// side circuits (mika):    speaker frequency = 3,4 / led pwm = 0,1 / sensor = 2
// center circuit (hannah): speaker frequency = 3,2 / led pwm = 0,1 / sensor = 4

// CENTER CIRCUIT ///////////////////////////////////////////////
#define f1 3
#define f2 2

#define sensorD 4
#define sensorA 2 // pin PB4 = ADC2
// turn pin PB3 on and off:
#define f1On() PORTB = 0b00001000
#define f1Off() PORTB = 0b00000000
// turn pin PB2 on and off:
#define f2On() PORTB = 0b00000100
#define f2Off() PORTB = 0b00000000

// SIDE CIRCUITS //////////////////////////////////////////////////
//#define f1 4
//#define f2 3
//
//#define sensorD 2
//#define sensorA 1 // pin PB2 = ADC1
//// turn pin PB4 on and off:
//#define f1On() PORTB = 0b00010000
//#define f1Off() PORTB = 0b00000000
//// turn pin PB3 on and off:
//#define f2On() PORTB = 0b00001000
//#define f2Off() PORTB = 0b00000000
////////////////////////////////////////////////////////

// Sensor:
int sensorValue;

float pwmIncrement;
int turn = 1;
boolean on = true;
unsigned long frequency;

void setup() {
  pinMode(f1, OUTPUT); 
  pinMode(f2, OUTPUT); 
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  //pinMode(sensorD, INPUT); //no internal pullup
  pinMode(sensorD, INPUT_PULLUP); // sets internal voltage divider/pullup resistor on analog input pin
} 	 



void loop() {  
  // read sensor value:
  sensorValue = analogRead(sensorA);
  if (sensorValue < 400) sensorValue = 400;
  frequency = 50 * sensorValue;
  
  if(sensorValue < 900) on = true;
    
    if(on == true && turn == 1) {
      play(f2, led2, frequency);
      on = false;
      turn = 2;
    }
    
    if(on == true && turn == 2) {
      play(f1, led1, frequency);
      turn = 1;
      on = false;
    }  

}

void play(int pin, int led, unsigned int freq){
  float halfT = 1000000.f / ((float)freq * 2.f);
  float pwmIncrement = 0.01;

  // fade ON:
  for(float i = 1; i < 254; i+=pwmIncrement){

    analogWrite(led, i);

    digitalWrite(pin, HIGH); //speakerOn();
    delayMicroseconds(halfT);
    digitalWrite(pin, LOW); //speakerOff();
    delayMicroseconds(halfT); 
  }

  // fade OFF:
  for(float i = 254; i > 1; i-=pwmIncrement){  

    analogWrite(led, i);

    digitalWrite(pin, HIGH); //speakerOn();
    delayMicroseconds(halfT);
    digitalWrite(pin, LOW); //speakerOff();
    delayMicroseconds(halfT); 
  }

  digitalWrite(led, LOW);

}












