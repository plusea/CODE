// cap-code - modded from elm-chans capacitive sensing code.


extern "C" 
{
  int boogieball(int);
}

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial (1);  // Tx pin 


#include "cs.h"
const int ciPinLed0 =  0;      // the number of the LED pin
const int ciPinLed1 =  2;      // the number of the LED pin

int ref[3], val[3],res[3],curon[2],oldon[2];


void get_sens (int *res, int chs)
{
  int ch, loop;
  
  /* Clear count accumlator */
  for (ch = 0; ch < chs; ch++) res[ch] = 0;

  /* Capture and accumlate integration time for 1/160 second */
  OCR0A = 8000000UL / 1024 / 160; // make sure that we are using ATTINY85 with 8MHz clock
  TCNT0 = 0;
  TIFR = _BV(OCF0A);
  TCCR0B = 0b011; //8

  loop = 0;

  do
  {
    for (ch = 0; ch < chs; ch++)
    {
      res[ch] += boogieball(ch);
    }
    loop++;    
  }
  while ((TIFR & _BV(OCF0A)) == 0);


  TCCR0B = 0;
  /* Mean calculation */
  for (ch = 0; ch < chs; ch++) 
  {
    res[ch] /= loop;
  }
}


void setup() 
{
  OSCCAL=146; // find this out first with tiny tuner or similar

  pinMode(ciPinLed0, OUTPUT);      
  pinMode(ciPinLed1, OUTPUT);      

  mySerial.begin(9600);
  mySerial.println("Calibrate thrice, first round:");  // this sets the outputs
  get_sens(ref, 2); 	/* Get reference count for each channel */
  mySerial.println("Second round.");  // this does the first baseline reference
  get_sens(ref, 2);
  mySerial.println("Third round.");   // this is just in case
  get_sens(ref, 2);
}


void loop()
{
  get_sens(val,2);  
  for(int dd=0;dd<2;dd++)
  {
    res[dd]=val[dd]-ref[dd];
  }


/*  transmit the values  */ 
/*
   mySerial.print("Values: ");
   mySerial.print(res[0]);
   mySerial.print("\t"); 
   mySerial.println(res[1]);
*/

/* do the math */
  for( int math=0;math<2;math++)
  {
    if( res[math] > 40 )
    {
      curon[math]=1;
    }
    else if( res[math]<38) // hysteresis
    {
      curon[math]=0;
    }
  }  
  
  
  /*  print out "button" status  */
  if( oldon[0]!=curon[0])
  {
    if( curon[0]==1)
    {
      mySerial.println("Left edge pressed.");
    }
    else
    {
      mySerial.println("Left edge released.");
    }
  }
  if( oldon[1]!=curon[1])
  {
    if( curon[1]==1)
    {
      mySerial.println("\t\tRight edge pressed.");
    }
    else
    {
      mySerial.println("\t\tRight edge released.");
    }   
  }

/*  update the outputs  */
  for( int a=0;a<40;a++)
  {
    if( res[0] < 4 )
    {
      asm("nop");
    }
    else if (res[0] < a ) 
    {
      PORTB &= ~0x01;      // direct port-handling for speed.
    }
    else 
    {
      PORTB |= 0x01;
    }

    if( res[1] < 4 )
    {
      asm("nop");
    }
    else if (res[1] < a ) 
    {     
      PORTB|=0x04;
    } 
    else 
    {
      PORTB&=~0x04;
    }
    // for POV..
    for(int d=0;d<200;d++)
    {
      asm("nop"); 
    }
  }


/*  update history  */
  oldon[0]=curon[0];
  oldon[1]=curon[1];
}







