#include <SPI.h>
#include <Adafruit_WS2801.h>
#include <Pixelgroup.h>

#include "WS2801Writer.h"


uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

// Adafruit_WS2801 does not provide an accessor for its internal pixels
// so we need to subclass Adafruit_WS2801 to create a pixelwriter we can use

// setup a pixelwriter
WS2801Writer pixelWriter(25, dataPin, clockPin);

//------------------------
// create pixelgroups

// instanciate with pixel indici

// argument 1: amount of pixels (e.g.: 3)
// argument 2..n: pixel indices (e.g.: 0, 1, 2)
Pixelgroup thegroup(3, 0, 1, 2);


void setup()
{  
  // init pixel writer (Adafruit_WS2801)
  pixelWriter.begin();
  
  
  //------------------------
  // manipulate group
  // demonstrate available functions
  
  // set pixels
  // argument 1: amount of pixels (e.g.: 4)
  // argument 2..n: pixel indices (e.g.: 4, 5, 6, 7)
  thegroup.setPixels(4, 4, 5, 6, 7);
  
  // clear pixel group
  thegroup.clear();
  
  // add pixels
  thegroup.addPixel(3);
  thegroup.addPixel(4);
  thegroup.addPixel(5);
  thegroup.addPixel(6);
  
  // remove a pixel
  thegroup.removePixel(4);
  
  
  //------------------------
  // set some colors, write them out
  thegroup.setRGB(255, 0, 0);
  writeGroups();
  
  delay(1000);
  
  // set some colors, write them out
  thegroup.setRGB(0, 255, 0);
  writeGroups();
  
  delay(1000);
  
  // set some colors, write them out
  thegroup.setRGB(0, 0, 255);
  writeGroups();
  
  delay(1000);

  
  //------------------------
  // setup fading of group thegroup
  thegroup.setFrom(255, 0, 0);
  thegroup.setTo(0, 0, 255);
  thegroup.setLoop(EASING_LOOP_BOUNCE);
  thegroup.setDuration(3000);
  thegroup.setEasing(true);


  //------------------------
  // set strobing of thatgroup
  thegroup.setOnTime(600); // in ms
  thegroup.setOffTimeSec(0.1); // or in sec
  thegroup.setStrobing(true);

  //------------------------
  // flickering?
  // randomly flickering pixels in group
  // value defines flickersteps
  // the higher the number, the longer it flickers
  thegroup.setFlicker(20);
}


void loop()
{
  // need to tick each group for animations like fading, strobing, flickering...
  // tick pickelgroups with same timestamp (so the animations are in sync)
  unsigned long _now = millis();
  
  thegroup.update(_now);
  
  // strip only gets written, if pixels are dirty
  writeGroups();
  
  delay(20);
}


void writeGroups()
{
  // paint the group to our pixelwriter
  thegroup.paint(pixelWriter);
  
  // only show pixel if pixelWriter is dirty
  pixelWriter.show();
}
