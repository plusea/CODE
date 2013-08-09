/*
  Modified Blink - Origanl is included with the Arduino IDE pacage.
 Turns on an LED on for one second, then off for one second, repeatedly.
 Uses IsTime() to control the flash rahter then the delay() function.
 
 David Fowler, AKA uCHobby, http://www.uchobby.com 01/21/2012
 Cut and paste from this text file into a new Arduino skectch
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(3, OUTPUT);     
}

unsigned long flashTimeMark=0;  //a millisecond time stamp used by the IsTime() function. initialize to 0
unsigned long int flashTimeInterval=1000;  //How many milliseconds we want for the flash cycle. 1000mS is 1 second.
unsigned long soundTimeMark=0;  //a millisecond time stamp used by the IsTime() function. initialize to 0
unsigned long int soundTimeInterval=10;  //How many milliseconds we want for the flash cycle. 1000mS is 1 second.

void loop() {
  if(IsTime(&flashTimeMark,flashTimeInterval)) {  //Is it time to toggle the LED?
    digitalWrite(3,!digitalRead(3)); //Read the LED state and NOT (!) it, write it back to the LED. This toggles
  }
  soundWithoutDelay();
}


void soundWithoutDelay(){
  if(IsTime(&soundTimeMark,10)) digitalWrite(4, HIGH);
  else digitalWrite(4, LOW);

}


//**********************************************************
//IsTime() function - David Fowler, AKA uCHobby, http://www.uchobby.com 01/21/2012

#define TIMECTL_MAXTICKS  4294967295L
#define TIMECTL_INIT      0

int IsTime(unsigned long *timeMark, unsigned long timeInterval){
  unsigned long timeCurrent;
  unsigned long timeElapsed;
  int result=false;

  timeCurrent=micros();
  if(timeCurrent<*timeMark) {  //Rollover detected
    timeElapsed=(TIMECTL_MAXTICKS-*timeMark)+timeCurrent;  //elapsed=all the ticks to overflow + all the ticks since overflow
  }
  else {
    timeElapsed=timeCurrent-*timeMark;  
  }

  if(timeElapsed>=timeInterval) {
    *timeMark=timeCurrent;
    result=true;
  }
  return(result);  
}



