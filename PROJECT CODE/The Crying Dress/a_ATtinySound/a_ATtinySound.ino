/*

 */
// mika = 0: pins 2,3 frequency, 5,6 LED
// hannah = 1:  
#include <avr/io.h>
// LED fade pins are fixed because of hardware PWM:
#define led1 0  // pin 5
#define led2 1  // pin 6

// speaker and sensor pins are vairable:
// HANNAH ///////////////////////////////////////////////
#define f1 3
#define f2 2
#define sensorD 4
#define sensorA 2 // pin PB4 = ADC2
// turn pin PB3 on and off:
#define f1On() PORTB |= 0b00000011
#define f1Off() PORTB &= ~0b00000011
// turn pin PB2 on and off:
#define f2On() PORTB |= 0b00000010
#define f2Off() PORTB &= ~0b00000010
////////////////////////////////////////////////////////

// MIKA //////////////////////////////////////////////////
//#define f1 4
//#define f2 3
//#define sensorD 2
//#define sensorA 1 // pin PB2 = ADC1
//// turn pin PB4 on and off:
//#define f1On() PORTB |= 0b00000100
//#define f1Off() PORTB &= ~0b00000100
//// turn pin PB3 on and off:
//#define f2On() PORTB |= 0b00000011
//#define f2Off() PORTB &= ~0b00000011
////////////////////////////////////////////////////////

int sensorValue = 0;
int timer = 0;
int frequency = 10000;

void setup() 	 
{ 	 
  pinMode(f1, OUTPUT); 
  pinMode(f2, OUTPUT); 
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 

  pinMode(sensorD, INPUT);
  digitalWrite(sensorA, HIGH);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
} 	 


void loop() 	// run over and over again
{ 	
  sensorValue = analogRead(sensorA);
  //if(sensorValue < 900) frequency = sensorValue;
  //else frequency = 1000;

  timer++;

  for (int x = 1; x < 254; x++){
    analogWrite(led1, x);
    cry(f1, frequency);
    delay(5);  

  }

  for (int x = 254; x > 1; x--){
    analogWrite(led1, x);
    cry(f1, frequency); 
    delay(5);  
  }

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
  delay(1000);

  for (int x = 1; x < 254; x++){
    analogWrite(led2, x);
    cry(f2, frequency);
    delay(5);  
  }

  for (int x = 254; x > 1; x--){
    analogWrite(led2, x);
    cry(f2, frequency);  
    delay(5);   
  }


  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
  delay(1000);

  //}
} 	

void fastCry(unsigned int freq){
  float halfT = 1000000.f / ((float)freq * 2.f);
  f1On();
  f2On();
  delayMicroseconds(halfT);
  f1Off();
  f2Off();
  delayMicroseconds(halfT);   
}

void cry(int pin, unsigned int freq){
  float halfT = 1000000.f / ((float)freq * 2.f);
  digitalWrite(pin, HIGH);
  delayMicroseconds(halfT);
  digitalWrite(pin, LOW);
  delayMicroseconds(halfT);   
}









//void analogVolume(){
//
//  for (int x = 1; x < 200; x++){
//    analogWrite(led1, x);
//    delay(40);
//  }
//
//  for (int x = 200; x > 1; x--){
//    analogWrite(led1, x);
//    delay(25);
//  }
//
//  digitalWrite(led1, LOW);
//  delay(2000);
//
//}
//
//
//
//
//void fade(){
//  for(int i=1; i < 254; i++){
//    analogWrite(0, i);
//    delay(20);
//  }
//  for(int i=254; i > 1; i--){
//    analogWrite(0, i);
//    delay(25);
//  }
//  digitalWrite(0, LOW);
//  delay(2000);
//}



//
//
//  // increase volume:
//  for(int v=0;v<255;v++) { 
//    for(int t=0;t<volumeSpeed;t++) {     	 
//      analogWrite(f1,v);
//      delayMicroseconds(frequency);
//      analogWrite(f1,0);
//      delayMicroseconds(frequency);
//    }
//  }
//
//  // decrease volume:
//  for(int v=254;v>0;v--) { 
//    for(int t=0;t<volumeSpeed;t++) {     	 
//      analogWrite(f1,v);
//      delayMicroseconds(frequency);
//      analogWrite(f1,0);
//      delayMicroseconds(frequency);
//    }	 
//  }
//
//  delay(2000);
















