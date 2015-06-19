#include <Adafruit_NeoPixel.h>
#include <Pixelgroup.h>


// adafuit strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, 6, NEO_GRB + NEO_KHZ800);

//------------------------
// setup a pixelwriter
// make sure rgb order is correct (default: GRB like neopixel)
PixelWriter pixelWriter(strip.getPixels(), (uint8_t)strip.numPixels(), PXW_GRB);


//------------------------
// create pixelgroup
// instanciate with pixel indices

// argument 1: amount of pixels (e.g.: 3)
// argument 2..n: pixel indices (e.g.: 0, 1, 2)
Pixelgroup thegroup(3, 0, 1, 2);


void setup()
{
  //------------------------
  // begin neopixel strip
  strip.begin();
 
  //------------------------
  // setup a callback for "show" function in pixelWriter
  pixelWriter.setShowFunc(showPixels);
 

  //------------------------
  // manipulate group
  // demonstrate available functions
  
    // set pixels
  // argument 1: amount of pixels (e.g.: 4)
  // argument 2..n: pixel indices (e.g.: 4, 5, 6, 7)
  thegroup.setPixels(4, 4, 5, 6, 7);
  
  // clear the group
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
  
  // tick this group with timestamp
  thegroup.update(_now);
  
  // strip only gets written, if pixels are dirty
  writeGroups();
  
  delay(20);
}


// callback function for pixelwriter
// only gets called if pixelwriter is dirty...
// pixelwriter is only dirty, if something changed in pixelgroups
void showPixels()
{
  strip.show();
}


void writeGroups()
{
  // paint the group to our pixelwriter
  thegroup.paint(pixelWriter);
  
  // we know we have set a callback function
  // can be tested with: pixelWriter.isShowFunc()
  
  // this will call our callback-function
  // pixelWriter is taking care about dirty state
  // only calls callback function if pixelwriter is dirty
  pixelWriter.show();
}
