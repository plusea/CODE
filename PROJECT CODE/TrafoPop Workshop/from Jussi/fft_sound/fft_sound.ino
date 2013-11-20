// fft

// goldfrapp - utopia
// massive attack - sly
// studio killers - ode to bouncer
// the verve - sonnet

#include "fix_fft.h"

int leds[6]={
  3,5,6,9,10,11};
int brgt[6]={
  0,0,0,0,0,0};

int old_data[6]={
  0,0,0,0,0,0};


char im[128];
char data[128]; 

int moo=0;
int audio_in=A3;


void setup() 
{                

  for(int i=0;i<6;i++)
  {
    pinMode(leds[i], OUTPUT);     
    analogWrite(leds[i],brgt[i]);
  }
  Serial.begin(115200);
}



void loop()
{
  int static i = 0;
  static long tt;
  int val;

// without millis, maximum frequency is about 3.5 kHz
//  if (millis() > tt)
//  {
    if (i < 128)
    {
//      ADCSRA&=0xF0;
//      ADCSRA|=0x03;
      val = analogRead(audio_in);
      data[i] = val / 4 - 128; // this is used to scale and to get rid of the mid-point
      im[i] = 0;
      i++;   

    }
    else
    {
      //this could be done with the fix_fftr function without the im array.
      fix_fft(data,im,7,0);
      // I am only interessted in the absolute value of the transformation
      for (i=0; i< 64;i++)
      {
        data[i] = sqrt(data[i] * data[i] + im[i] * im[i]); 
      }



      for( int meh=0;meh<64;meh++)
      {
        if( data[meh]>6) // 7
        {
          Serial.print("@");
        }
        else if( data[meh] >4 ) //5| whole thing SENSITIVE NOW
        {
          Serial.print("0");      
        }
        else if( data[meh] >2 ) // 3, not used
        {
          Serial.print("*");      
        }
        else if( data[meh] >1 ) 
        {
          Serial.print(",");      
        }
        else
        {
          Serial.print(".");
        }
      }
      Serial.println("");


    }

//    tt = millis();
//  }

  /*
  brgt[0]=255-data[0]*16; //0-500
   brgt[1]=255-data[1]*16; //500-1000
   brgt[2]=255-data[2]*16; //1000-1500
   brgt[3]=255-data[3]*16; //1500-2000
   brgt[4]=255-data[4]*16; //2000-2500
   brgt[5]=255-data[5]*16; //2500-3000
   
   
   
   
   analogWrite(leds[0],brgt[0]);
   analogWrite(leds[1],brgt[1]);
   analogWrite(leds[2],brgt[2]);
   analogWrite(leds[3],brgt[3]);
   analogWrite(leds[4],brgt[4]);
   analogWrite(leds[5],brgt[5]);
   */
}




