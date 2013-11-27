
// touch code for knitted thingie

extern "C" 
{
  int boogieball(int);
}

//#include <SendOnlySoftwareSerial.h>
//SendOnlySoftwareSerial mySerial (1);  // Tx pin 

#include "cs.h"

int ref[4], val[4],res[4],curon[2],oldon[2];


int led[]={
 0,1,2};
int numberPins = 3;
int numberCharlies = 6;
int charliePin;


void charliePlex(int myLed){
 switch(myLed){
   // 1
 case 5:
   pinMode(0, OUTPUT);
   pinMode(1, OUTPUT);
   pinMode(2, INPUT);
   digitalWrite(0, LOW);
   charliePin = 1;
   break;

   // 2
 case 6:
   pinMode(0, OUTPUT);
   pinMode(1, OUTPUT);
   pinMode(2, INPUT);
   digitalWrite(1, LOW);
   charliePin = 0;
   break;

   // 3
 case 1:
   pinMode(0, INPUT);
   pinMode(1, OUTPUT);
   pinMode(2, OUTPUT);
   digitalWrite(1, LOW);
   charliePin = 2;
   break;

   // 4
 case 2:
   pinMode(0, INPUT);
   pinMode(1, OUTPUT);
   pinMode(2, OUTPUT);
   digitalWrite(2, LOW);
   charliePin = 1;
   break;

   // 5
 case 3:
   pinMode(0, OUTPUT);
   pinMode(1, INPUT);
   pinMode(2, OUTPUT);
   digitalWrite(0, LOW);
   charliePin = 2;
   break;

       // 6
 case 4:
   pinMode(0, OUTPUT);
   pinMode(1, INPUT);
   pinMode(2, OUTPUT);
   digitalWrite(2, LOW);
   charliePin = 0;
   break;
 }
}


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
  OSCCAL=140;

  for( int i=0;i<6;i++)
  {
   charliePlex(i+1);
   digitalWrite(charliePin, HIGH); 
//   delay(500);
   digitalWrite(charliePin, LOW);
  }

//  mySerial.begin(9600);
//  mySerial.println("Calibrate thrice, first round:");  // this sets the outputs
  get_sens(ref, 2); 	/* Get reference count for each channel */
   charliePlex(1);
   digitalWrite(charliePin, HIGH); 
//   delay(500);
   digitalWrite(charliePin, LOW);

//  mySerial.println("Second round.");  // this does the first baseline reference
  get_sens(ref, 2);
   charliePlex(3);
   digitalWrite(charliePin, HIGH); 
//   delay(500);
   digitalWrite(charliePin, LOW);
//  mySerial.println("Third round.");   // this is just in case
  get_sens(ref, 2);

   charliePlex(6);
   digitalWrite(charliePin, HIGH); 
//   delay(500);
   digitalWrite(charliePin, LOW);
}


void loop()
{
  get_sens(val,2);  
  for(int dd=0;dd<2;dd++)
  {
    res[dd]=val[dd]-ref[dd];
  }


/*  transmit the values  */ 


/*   mySerial.print("Values: ");
   mySerial.print(res[0]);
   mySerial.print("\t"); 
   mySerial.print(res[1]);
   mySerial.print("\t"); 
   mySerial.println(res[0]-res[1]);
   */
   int value = map(res[0]-res[1], -20,20, 6,1);
   digitalWrite(charliePin, LOW);
   charliePlex(value);
   
   if( (res[0] > 8) || (res[1] > 8) )
   {
     digitalWrite(charliePin, HIGH); 
   }
   


/*   mySerial.print("\t"); 
   mySerial.print(res[2]);
   mySerial.print("\t"); 
   mySerial.println(res[3]);
*/

/* do the math */
/*
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
  
  /*
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
*/

/*  update the outputs  */

/*
   digitalWrite(charliePin, LOW); 
   charliePlex(i+1);
   digitalWrite(charliePin, HIGH);
*/

/*  for( int a=0;a<40;a++)
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







