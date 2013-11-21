// code for trafopop jacket
// written by jussi
// modified by hannah

#include <SPI.h>
#include "fix_fft.h"

#define NUM 46

typedef struct color
{
  byte r, g, b;
}
color;

color pixels[NUM];

char im[128];
char data[128]; 

int moo=0;
int audio_in=3;


struct color colorOFF = { 
  1,1,1 };

struct color colorON = { 
  255, 255, 255 };

struct color colorRed = { 
  255, 1, 1 };

struct color colorYellow = { 
  255, 255, 1 };

struct color colorTurquoise = { 
  1, 255, 255 };

struct color colorPurple = { 
  255, 1, 255 };




void setup() 
{                
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  // SPI.setClockDivider(SPI_CLOCK_DIV16);  // 1 MHz
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // 2 MHz


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

    struct color color2 =
    {
      0, 0, 0
    };

    // the code checks for three frequency bands at the same time, if any of the three is higher
    // than threshold value (6, 4, 2, or 1), then lights are set up accordingly.

    // the volumes (or energy) per frequency band is in data[x]
    // in this case, the data is used from slots of 0 -> 60.
    // first led is lit by values from 0-2, second with values from 3-5, etc.


    graphWithColor();
    //graphwithPosition();  

    show2((byte *)pixels, sizeof(pixels));

  }

  //    tt = millis();
  //  }


}








void show2(byte *bytes, int size)
{
  for (int index=0; index<size; index++)
  {
    // nur 25% Helligkeit    
    byte c = bytes[index] >> 2;

    for (SPDR = c; !(SPSR & _BV(SPIF)););
  }
}



