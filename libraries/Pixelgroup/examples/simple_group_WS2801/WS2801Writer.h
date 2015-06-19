/*
* Writer class for WS2801.
* don't write to WS2801, if class is not dirty
*/


#ifndef WS2801_WRITER_H
#define WS2801_WRITER_H

#include <Adafruit_WS2801.h>
#include <pixelWriterInterface.h>

//--------------------------------------------------------
// WS2801Writer:
//	subclass of Adafruits WS2801
//	implementing pixelWriterInterface
class WS2801Writer : public Adafruit_WS2801, public PixelWriterInterface
{
public:
  WS2801Writer(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order=WS2801_RGB);
  
  // satisfy interface  
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
  void setPixelColor(uint16_t n, uint32_t c);
  void show();  
};


#endif
