/*
  thanks to ingo for help with this code!!!
 this code demondatrates the use of timer interrupts on an ATtiny 45.
 we use the timer interrupt to create a frequency for a speaker
 and harware pwm to slowly fade an LED on and off.
 we do this so that the delay() function called to control the 
 speed of the fading LED does not interfere with the speed of the frequency.
 */

// LED fade pins are fixed because of hardware PWM:
#define led1 0  // pin 5
#define led2 1  // pin 6

// DIFFERENT CIRCUITS, DIFFERENT PINS /////////////////////
// side circuits (mika):    speaker frequency = 3,4 / led pwm = 0,1 / sensor = 2
// center circuit (hannah): speaker frequency = 3,2 / led pwm = 0,1 / sensor = 4
// CENTER ///////////////////////////////////////////////
//#define f1 3
//#define f2 2
//#define sensorD 4
//#define sensorA 2 // pin PB4 = ADC2
//// turn pin PB3 on and off:
//#define f1On() PORTB = 0b00001000
//#define f1Off() PORTB = 0b00000000
//// turn pin PB2 on and off:
//#define f2On() PORTB = 0b00000100
//#define f2Off() PORTB = 0b00000000

// SIDES //////////////////////////////////////////////////
#define f1 4
#define f2 3
#define sensorD 2
#define sensorA 1 // pin PB2 = ADC1
// turn pin PB4 on and off:
#define f1On() PORTB = 0b00010000
#define f1Off() PORTB = 0b00000000
// turn pin PB3 on and off:
#define f2On() PORTB = 0b00001000
#define f2Off() PORTB = 0b00000000
////////////////////////////////////////////////////////




// timer interrupt variables:
int flip = 0;
unsigned int latency;

unsigned int tcnt; // global
int turn = 0; // global

void SetupTimer0()
{
  /* Configure timer2 in normal mode (pure counting, no PWM etc.) */
  //TCCR1 &= ~((1<<WGM11) | (1<<WGM10));  
  //TCCR1B &= ~(1<<WGM12);  

  /* Select clock source: internal I/O clock */
  //ASSR &= ~(1<<AS2); 

  /* Disable Compare Match A interrupt enable (only want overflow) */
  TIMSK &= ~(1<<OCIE1A);

  /* Now configure the prescaler to CPU clock divided by 1024 */
  TCCR1 = 1<<CS10 | 1<<CS11 | 1<<CS12 | 0<<CS13; // sets timer prescale to /64

  /* We need to calculate a proper value to load the timer counter. 
   * The following loads the value 131 into the Timer 2 counter register 
   * The math behind this is: 
   * (CPU frequency) / (prescaler value) = 15625 Hz = 64us. 
   * (desired period) / 64us = 8. 
   * MAX(uint8) - 8 = 248; 
  /* Save value globally for later reload in ISR */
  tcnt = 128;


  /* Finally load end enable the timer */
  TCNT1 = tcnt;  
  TIMSK |= (1<<TOIE1);  // turn it on
}





//Timer2 overflow interrupt vector handler //alle 512 us
//this is the light callback
ISR(TIMER1_OVF_vect) {

  //-------------
  //do the work, be quick
  //---------------
  if (flip) {
    if(turn == 1) f1On();
    if(turn == 2) f2On();
    flip = 0;
  } 
  else {
    if(turn == 1) f1Off();
    if(turn == 2) f2Off();
    flip = 1;
  }

  //Capture the current timer value. This is how much error we have
  //due to interrupt latency and the work in this function
  latency = TCNT1;
  //Reload the timer and correct for latency.
  TCNT1 = latency+tcnt;
  //or just reload tcnt2
  //TCNT2 = tcnt2;
}






void setup() {
  pinMode(f1, OUTPUT); 
  pinMode(f2, OUTPUT); 
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  pinMode(sensorD, INPUT);
  digitalWrite(sensorD, HIGH);  // set internal pul-up resistor on analog input pin
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  SetupTimer0();
} 	 






// loop variables:
int sensorValue = 0;
int fadeDuration = 5;
int fadeDelay = 1000;
int maxThreshold = 300;
int minThreshold = 10;
int frequency = 0;

void loop() {
  sensorValue = analogRead(sensorA);  // water sensor tested to be roughly between 100 - 700
  
  // CODE TO TEST WITH: ////////////////////////////////////////
  //  if(sensorValue < 200) digitalWrite(led1, HIGH);
  //  else digitalWrite(led1, LOW);
  //  turn = 1;
  //  analogWrite(led1, sensorValue/2);
  //  tcnt = 254 - sensorValue/9;
  //  delay(sensorValue);
  //  digitalWrite(led1, LOW);
  //  delay(sensorValue);
  ////////////////////////////////////////////////////////////////

tcnt = 220;
turn = 1;
pwmLED(led1, fadeDuration, fadeDelay);

tcnt = 246;
turn = 2;
pwmLED(led2, fadeDuration, fadeDelay);

//  if(sensorValue < maxThreshold && sensorValue > minThreshold) {  // if sensor value falls between thresholds
//    // FREQUENCY of SPEAKER dependant on SENSOR VALUE:  
//    frequency = 254 - sensorValue/9;  // scale sensorValue to roughly [0-255]
//    tcnt = frequency; // use this value to pre-load the timer with
//
//    // PWM of LED dependant on SENSOR VALUE:
//    fadeDuration = 5; //sensorValue/18;
//
//    // randomly flip between first and second LED (and speaker) depending on odd or even sensorValue:
//    if(sensorValue % 2 == 0) {
//      turn = 1;
//      pwmLED(led1, fadeDuration, fadeDelay);
//    }
//
//    else {
//      turn = 2;
//      pwmLED(led2, fadeDuration, fadeDelay);
//    }
//
//  } // end if(threshold)
}



void pwmLED(int pin, int _pwmDuration, int _pwmDelay){

  // PWM of LED:
  for (int x = 1; x < 254; x++){
    analogWrite(pin, x);
    delay(_pwmDuration);  
  }
  for (int x = 254; x > 1; x--){
    analogWrite(pin, x);
    delay(_pwmDuration);  
  }
  // PAUSE
  turn = 0;
  digitalWrite(pin, LOW);

}








