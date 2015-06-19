  /*
  thanks to ingo for help with this code!!!
  this code demondatrates the use of timer interrupts on an ATtiny 45.
  we use the timer interrupt to create a frequency for a speaker
  and harware pwm to slowly fade an LED on and off.
  we do this so that the delay() function called to control the 
  speed of the fading LED does not interfere with the speed of the frequency.
 */


// LED fade pin uses hardware PWM:
#define led1 0  // pin 5

#define f1 3 // frequency to be played

// turn pin PB3 on and off:
#define f1On() PORTB = 0b00001000
#define f1Off() PORTB = 0b00000000

int _flip = 0;

unsigned int latency;
unsigned int tcnt0; 


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
  tcnt0 = 128;

  /* Finally load end enable the timer */
  TCNT1 = tcnt0;  
  TIMSK |= (1<<TOIE1);  // turn it on
}

//Timer2 overflow interrupt vector handler //alle 512 us
//this is the light callback
ISR(TIMER1_OVF_vect) {

  //-------------
  //do the work, be quick
  //---------------

  if (_flip) {
    f1On();
    _flip = 0;
  } 
  else {
    f1Off();
    _flip = 1;
  }
  
  //Capture the current timer value. This is how much error we have
  //due to interrupt latency and the work in this function
  latency=TCNT1;
  //Reload the timer and correct for latency.
  TCNT1 = latency+tcnt0;

  //or just reload tcnt2
  //TCNT2 = tcnt2;
}



void setup() 	 
{
  pinMode(f1, OUTPUT); 
  pinMode(led1, OUTPUT); 
  SetupTimer0();
} 	 



void loop(){
  for (int x = 1; x < 254; x++){
    analogWrite(led1, x);
    delay(15);  
  }

  for (int x = 254; x > 1; x--){
    analogWrite(led1, x);
    delay(15);  
  }

  digitalWrite(led1, LOW);
  delay(1000);

} 
