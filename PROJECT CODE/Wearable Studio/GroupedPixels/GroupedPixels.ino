#include <Adafruit_NeoPixel.h>
#include <Pixelgroup.h>


// adafuit strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(28, 6, NEO_GRB + NEO_KHZ800);

//------------------------
// setup a pixelwriter
// make sure rgb order is correct (default: GRB like neopixel)
PixelWriter pixelWriter(strip.getPixels(), (uint8_t)strip.numPixels(), PXW_GRB);


//------------------------
// create pixelgroup
// instanciate with pixel indices

// argument 1: amount of pixels (e.g.: 3)
// argument 2..n: pixel indices (e.g.: 0, 1, 2)
Pixelgroup group1(7, 0,1,2,3,4,5,6);
Pixelgroup group2(7, 7,8,9,10,11,12,13);
Pixelgroup group3(7, 14,15,16,17,18,19,20);
Pixelgroup group4(7, 21,22,23,24,25,26,27);


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
  //group1.setPixels(28, 4, 5, 6, 7);
  
  // clear the group
  //group1.clear();
  
  // add pixels
  //group1.addPixel(3);
  
  // remove a pixel
  //group1.removePixel(4);
  
  
  //------------------------
  // set some colors, write them out
  group1.setRGB(255, 0, 0);
  group2.setRGB(0, 255, 0);
  group3.setRGB(0, 0, 255);
  group4.setRGB(200, 255, 0);
  writeGroups();
  
  //------------------------
  // setup fading of group thegroup
  group1.setFrom(255, 0, 0);
  group1.setTo(0, 0, 255);
  group1.setLoop(EASING_LOOP_BOUNCE);
  group1.setDuration(3000);
  group1.setEasing(true);


  //------------------------
  // set strobing of thatgroup
//  group1.setOnTime(600); // in ms
//  group1.setOffTimeSec(0.1); // or in sec
//  group1.setStrobing(true);

  //------------------------
  // flickering?
  // randomly flickering pixels in group
  // value defines flickersteps
  // the higher the number, the longer it flickers
  //group1.setFlicker(20);
  

}


void loop()
{
  // need to tick each group for animations like fading, strobing, flickering...
  // tick pickelgroups with same timestamp (so the animations are in sync)
  unsigned long _now = millis();
  
  // tick this group with timestamp
  group1.update(_now);
//  group2.update(_now);
//  group3.update(_now);
//  group4.update(_now);
  
  // strip only gets written, if pixels are dirty
  writeGroups();
  
  delay(20);
}


// callback function for pixelwriter
// only gets called if pixelwriter is dirty...
// pixelwriter is only dirty, if something changed in pixelgroups
void showPixels(){
  strip.show();
}


void writeGroups()
{
  // paint the group to our pixelwriter
  group1.paint(pixelWriter);
  group2.paint(pixelWriter);
  group3.paint(pixelWriter);
  group4.paint(pixelWriter);
  
  // we know we have set a callback function
  // can be tested with: pixelWriter.isShowFunc()
  
  // this will call our callback-function
  // pixelWriter is taking care about dirty state
  // only calls callback function if pixelwriter is dirty
  pixelWriter.show();
}
