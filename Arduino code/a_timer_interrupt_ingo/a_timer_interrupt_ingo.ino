unsigned int latency;
unsigned int tcnt2; 

void SetupTimer2(){

/* Configure timer2 in normal mode (pure counting, no PWM etc.) */  
TCCR2A &= ~((1<<WGM21) | (1<<WGM20));  
TCCR2B &= ~(1<<WGM22);  

/* Select clock source: internal I/O clock */  
ASSR &= ~(1<<AS2);  

/* Disable Compare Match A interrupt enable (only want overflow) */  
TIMSK2 &= ~
(1<<OCIE2A);

/* Now configure the prescaler to CPU clock divided by 1024 */
TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20;

/* We need to calculate a proper value to load the timer counter. 
 * The following loads the value 131 into the Timer 2 counter register 
 * The math behind this is: 
 * (CPU frequency) / (prescaler value) = 15625 Hz = 64us. 
 * (desired period) / 64us = 8. 
 * MAX(uint8) - 8 = 248; 
 */  
/* Save value globally for later reload in ISR */  
tcnt2 = 248;

/* Finally load end enable the timer */  
TCNT2 = tcnt2;  
TIMSK2 |= (1<<TOIE2);
}


//Timer2 overflow interrupt vector handler //alle 512 us
//this is the light callback
ISR(TIMER2_OVF_vect) {

//-------------
//do the work, be quick
//---------------

//Capture the current timer value. This is how much error we have
//due to interrupt latency and the work in this function
latency=TCNT2;
//Reload the timer and correct for latency.
TCNT2 = latency+tcnt2;

//or just reload tcnt2
//TCNT2 = tcnt2;
}
