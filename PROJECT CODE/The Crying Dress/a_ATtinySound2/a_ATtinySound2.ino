/*

 */
// mika = 0: pins 2,3 frequency, 5,6 LED
// hannah = 1:  

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
#define f1On() PORTB = 0b00001000
#define f1Off() PORTB = 0b00000000
// turn pin PB2 on and off:
#define f2On() PORTB |= 0b00000100
#define f2Off() PORTB &= ~0b00000000

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
   */
  /* Save value globally for later reload in ISR */
  if(frequency == 1) tcnt0 = 240;
  if(frequency == 2) tcnt0 = 250;

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
    f2On();
    _flip = 0;
  } 
  else {
    f1Off();
    f2Off();
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
  pinMode(f2, OUTPUT); 
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 

  pinMode(sensorD, INPUT);
  digitalWrite(sensorA, HIGH);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  SetupTimer0();
} 	 









void loop(){
  sensorValue = analogRead(sensorA);
  //if(sensorValue < 900) frequency = sensorValue;
  //else frequency = 1000;

  frequency = 1;

  for (int x = 1; x < 254; x++){
    analogWrite(led1, x);
    delay(15);  
  }

  for (int x = 254; x > 1; x--){
    analogWrite(led1, x);
    //cry(f1, frequency); 
    delay(15);  
  }

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
  delay(1000);
  
    frequency = 2;
  
    for (int x = 1; x < 254; x++){
    analogWrite(led2, x);
    //cry(f1, frequency);
    delay(15);  
  }

  for (int x = 254; x > 1; x--){
    analogWrite(led2, x);
    //cry(f1, frequency); 
    delay(15);  
  }

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
  delay(1000);
  
  
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


















