
// taken from: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=68397&start=0

#include <avr/io.h>
#include <util/delay.h>

void wait(void);

int main (void)
{
   
   // set PORTB for output
   DDRB = 0x3F;
   
   //Declare and Initialize Delay Loop Counter variable "i"
   int i = 1;
   
   while(1)
   {
   
      for(i=0;i<255;i++)
      {
         PORTB = 0x02;

         _delay_loop_2(600);
      }
            for(i=0;i<255;i++)
      {
         PORTB = 0x00;

         _delay_loop_2(600);
      }
//      
//      for(i=0;i<255;i++)
//      {
//         PORTB = 0x18;
//            
//         _delay_loop_2(300);
//      }
//            
//      for(i=0;i<255;i++)
//      {
//         PORTB = 0x21;   
//            
//         _delay_loop_2(300);
//      }
//            
//            
//      for(i=0;i<255;i++)
//      {
//         PORTB = 0x34;
//            
//         _delay_loop_2(300);
//      }
      
   }
   
}

