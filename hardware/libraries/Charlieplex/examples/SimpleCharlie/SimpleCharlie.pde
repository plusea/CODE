/*
||
|| @author Alexander Brevig
|| @version 1.0
||
*/
/*
This code is tested with built in led @ pin 13, a led connected with anode 12 cathode 13, and a last led connected with anode 11 cathode 13 
I would love feedback at alexanderbrevig@gmail.com
*/

#include <Charlieplex.h>

#define NUMBER_OF_PINS 3
//define pins in the order you want to adress them
byte pins[] = {11,12,13};

//initialize object
Charlieplex charlieplex = Charlieplex(pins,NUMBER_OF_PINS);

//individual 'pins' , adress charlieplex pins as you would adress an array
charliePin led1 = { 1 , 2 }; //led1 is indicated by current flow from 12 to 13
charliePin led2 = { 2 , 1 };
charliePin led3 = { 0 , 2 };

boolean singleOn = false;


void setup(){ /*nothing*/ }

void loop(){
  if (singleOn){ charlieplex.clear(); }
  
  charlieplex.charlieWrite(led1,HIGH);
  delay(1000);
  charlieplex.charlieWrite(led2,HIGH);
  delay(1000);
  charlieplex.charlieWrite(led3,HIGH);
  delay(1000);
  
  singleOn=!singleOn;
}

