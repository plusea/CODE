/*
* Writer class for Adafruit_WS2801
* don't write to if class is not dirty
*/

#include "WS2801Writer.h"

WS2801Writer::WS2801Writer(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order) : 
  Adafruit_WS2801(n, dpin, cpin, order)
{
  setDirty(true);
}


// implement interface
void WS2801Writer::show()
{
  if (isDirty()) {
    // call show in Adafruit_WS2801
    Adafruit_WS2801::show();
  
    setDirty(false);
  }  
}

void WS2801Writer::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
  Adafruit_WS2801::setPixelColor(n, r, g, b);
  setDirty(true);
}

void WS2801Writer::setPixelColor(uint16_t n, uint32_t c)
{
  Adafruit_WS2801::setPixelColor(n, c);
  setDirty(true);
}
