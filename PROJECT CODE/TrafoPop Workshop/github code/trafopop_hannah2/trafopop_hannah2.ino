#include <SPI.h>

#define NUM 20





long framecount = 0;
int fadeCount = 0;
int fadeAmount = 1;
int sensorValue;
float red;
float green;
float blue;
int count;
boolean setPosition = false;



typedef struct color
{
  byte r, g, b;
}
color;

color pixels[NUM];

#if 0
inline char normalizedX(byte index)
{
  return pointX[index];
}

inline char normalizedY(byte index)
{
  return pointY[index];
}
#else
inline char normalizedX(byte index)
{
  return index/10;
}

inline char normalizedY(byte index)
{
  return index%10;
}
#endif

typedef struct CGPoint
{
  float x;
  float y;
}
CGPoint;





inline struct CGPoint CGPointMake(float x, float y)
{
  struct CGPoint point;

  point.x = x;
  point.y = y;

  return point;
}


struct color colorOFF =
{ 
  0,0,0
};

struct color colorON =
{ 
  254, 254, 254
};



inline float distance(CGPoint a, CGPoint b)
{
  float x = a.x - b.x;
  float y = a.y - b.y;

  //  return sqrt(x*x + y*y);
  return (x*x + y*y);
}





inline CGPoint normalize(CGPoint p)
{
  float length = sqrt(p.x*p.x + p.y*p.y);

  return CGPointMake(p.x/length, p.y/length);
}





void show(byte *bytes, int size)
{
  for (int index=0; index<size; index++)
  {
    // nur 25% Helligkeit    
    byte c = bytes[index] >> 2;

    for (SPDR = c; !(SPSR & _BV(SPIF)););
  }
}




void setup()
{
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV16);  // 1 MHz
  //SPI.setClockDivider(SPI_CLOCK_DIV8);  // 2 MHz
  // SPI.setClockDivider(SPI_CLOCK_DIV4);  // 4 MHz 

  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(A1, INPUT_PULLUP);
  digitalWrite(14, LOW);
  digitalWrite(16, HIGH);
  Serial.begin(9600);


}



void loop()
{
  sensorValue = analogRead(A1);
  sensorValue = map(sensorValue, 0, 1000, 0, NUM);
  Serial.println(sensorValue);
  if(sensorValue != 20) {
    draw4();
    show((byte *)pixels, sizeof(pixels));
    delay(2);
  }
}







