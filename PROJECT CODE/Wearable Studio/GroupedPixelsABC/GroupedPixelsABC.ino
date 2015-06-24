#include <Adafruit_NeoPixel.h>
#include <Pixelgroup.h>

#define randomMax 50

// adafuit strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(186, 6, NEO_GRB + NEO_KHZ800);

//------------------------
// setup a pixelwriter
// make sure rgb order is correct (default: GRB like neopixel)
PixelWriter pixelWriter(strip.getPixels(), (uint8_t)strip.numPixels(), PXW_GRB);


//------------------------
// create pixelgroup
// instanciate with pixel indices

// argument 1: amount of pixels (e.g.: 3)
// argument 2..n: pixel indices (e.g.: 0, 1, 2)
Pixelgroup segment0(40, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39);
Pixelgroup segment1(10, 40,41,42,43,44,45,46,47,48,49);
Pixelgroup segment2(10, 50,51,52,53,54,55,56,57,58,59);
Pixelgroup segment3(20, 60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79);
Pixelgroup segment4(13, 80,81,82,83,84,85,86,87,88,89,90,91,92);
Pixelgroup segment5(13, 93,94,95,96,97,98,99,100,101,102,103,104,105);
Pixelgroup segment6(11, 106,107,108,109,110,111,112,113,114,115,116);
Pixelgroup segment7(11, 117,118,119,120,121,122,123,124,125,126,127);
Pixelgroup segment8(16, 128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143);
Pixelgroup segment9(10, 144,145,146,147,148,149,150,151,152,153);
Pixelgroup segment10(8, 154,155,156,157,158,159,160,161);
Pixelgroup segment11(24,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185);

Pixelgroup segment0a(40, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39);
Pixelgroup segment0b(40, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39);
Pixelgroup segment0c(40, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39);
Pixelgroup segment0d(40, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39);

Pixelgroup segment3a(11, 60,61,62,63,64,65,66,67,68,69,70);
Pixelgroup segment3b(9, 71,72,73,74,75,76,77,78,79);

Pixelgroup segment4a(9, 84,85,86,87,88,89,90,91,92);
Pixelgroup segment4b(4, 80,81,82,83);

Pixelgroup segment8a(6, 128,129,130,131,132,133);
Pixelgroup segment8b(10, 134,135,136,137,138,139,140,141,142,143);

Pixelgroup segment9a(4, 150,151,152,153);
Pixelgroup segment9b(6, 144,145,146,147,148,149);

Pixelgroup segment11a(3, 162,163,164);
Pixelgroup segment11b(12, 165,166,167,168,169,170,171,172,173,174,175,176);
Pixelgroup segment11c(3, 178,179,180);
Pixelgroup segment11d(3, 183,184,185);




void setup()
{
  //------------------------
  // begin neopixel strip
  strip.begin();

  //------------------------
  // setup a callback for "show" function in pixelWriter
  pixelWriter.setShowFunc(showPixels);


  //------------------------
  // manipulate segment
  // demonstrate available functions

    // set pixels
  // argument 1: amount of pixels (e.g.: 4)
  // argument 2..n: pixel indices (e.g.: 4, 5, 6, 7)
  //group1.setPixels(28, 4, 5, 6, 7);

  // clear the segment
  //group1.clear();

  // add pixels
  //group1.addPixel(3);

  // remove a pixel
  //group1.removePixel(4);


  //------------------------
  // set some colors, write them out
  segment0.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment1.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment2.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment3.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment4.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment5.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment6.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment7.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment8.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment9.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment10.setRGB(random(randomMax), random(randomMax), random(randomMax));
  segment11.setRGB(random(randomMax), random(randomMax), random(randomMax));
  writeGroups();
  
  colorWipe(strip.Color(0, 0, 0), 100); // Red
  
//  segment1.setRGB(50,0,0);
//  segment2.setRGB(0,50,0);
//  segment3.setRGB(0,0,);
//  segment4.setRGB(50,200,0);
//  segment5.setRGB(50,200,0);
//  segment6.setRGB(50,200,0);
//  segment7.setRGB(50,200,0);
//  segment8.setRGB(50,200,0);
//  segment9.setRGB(50,200,0);
//  segment10.setRGB(50,200,0);
//  segment11.setRGB(50,200,0);
//  writeGroups();

  //------------------------
  // setup fading of segment thegroup
//  segment1.setFrom(255, 0, 0);
//  segment1.setTo(0, 0, 255);
//  segment1.setLoop(EASING_LOOP_BOUNCE);
//  segment1.setDuration(3000);
//  segment1.setEasing(true);


  //------------------------
  // set strobing of thatgroup
  //  segment1.setOnTime(600); // in ms
  //  segment1.setOffTimeSec(0.1); // or in sec
  //  segment1.setStrobing(true);

  //------------------------
  // flickering?
  // randomly flickering pixels in segment
  // value defines flickersteps
  // the higher the number, the longer it flickers
  //group1.setFlicker(20);


}


void loop()
{
  char input = 'a';
  ABC_funk(input);
  // need to tick each segment for animations like fading, strobing, flickering...
  // tick pickelgroups with same timestamp (so the animations are in sync)
  unsigned long _now = millis();

  // tick this segment with timestamp
  //group1.update(_now);
  //  segment2.update(_now);
  //  segment3.update(_now);
  //  segment4.update(_now);

  // strip only gets written, if pixels are dirty
  //writeGroups();

}


// callback function for pixelwriter
// only gets called if pixelwriter is dirty...
// pixelwriter is only dirty, if something changed in pixelgroups
void showPixels(){
  strip.show();
}


void writeGroups()
{
  // paint the segment to our pixelwriter
  segment0.paint(pixelWriter);
  segment1.paint(pixelWriter);
  segment2.paint(pixelWriter);
  segment3.paint(pixelWriter);
  segment4.paint(pixelWriter);
  segment5.paint(pixelWriter);
  segment6.paint(pixelWriter);
  segment7.paint(pixelWriter);
  segment8.paint(pixelWriter);
  segment9.paint(pixelWriter);
  segment10.paint(pixelWriter);
  segment11.paint(pixelWriter);

  // we know we have set a callback function
  // can be tested with: pixelWriter.isShowFunc()

  // this will call our callback-function
  // pixelWriter is taking care about dirty state
  // only calls callback function if pixelwriter is dirty
  pixelWriter.show();
}

