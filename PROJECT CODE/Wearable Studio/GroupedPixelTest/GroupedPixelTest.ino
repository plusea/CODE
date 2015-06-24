#include <Adafruit_NeoPixel.h>
#include <Pixelgroup.h>


// adafuit strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(186, 6, NEO_GRB + NEO_KHZ800);

//------------------------
// setup a pixelwriter
// make sure rgb order is correct (default: GRB like neopixel)
PixelWriter pixelWriter(strip.getPixels(), (uint8_t)strip.numPixels(), PXW_GRB);



byte segments[22][11];


void segmentHelper(int number,int start,int length){
 for (int i=0;i<=11;i++){
   if (i < length){
     segments[number][i] = start + i;
   } else{
     segments[number][i]= 255;
   }
 } 
  
}

//a segment11c, segment10, segment9, segment8b
byte alphabetSoup [27][12]= {
 {10,11,12,13,14,17,18,19,255,255,255,255},
 {3,5,11,13,14,17,18,19,255,255,255,255},
 {5,14,17,18,19,255,255,255,255,255,255,255},
 {9,16,17,18,19,20,255,255,255,255,255,255},
 {0,5,14,16,17,18,19,255,255,255,255,255},
 {0,255,14,16,17,18,19,255,255,255,255,255}, 
 {0,1,2,3,11,13,14,255,255,255,255,255},
 {10,11,12,13,17,18,19,255,255,255,255,255},
 {0,1,5,16,17,18,19,20,255,255,255,255},
 {16,17,18,19,20,255,255,255,255,255,255,255},
 {3,11,17,18,19,255,255,255,255,255,255,255},
 {5,15,16,17,18,19,255,255,255,255,255,255},
 {7,8,9,19,255,255,255,255,255,255,255,255},
 {3,12,13,18,19,255,255,255,255,255,255,255},
 {5,12,13,14,17,18,19,255,255,255,255,255},
 {10,11,13,14,17,18,19,255,255,255,255,255},
 {3,11,12,13,14,17,255,255,255,255,255,255},
 {3,11,13,14,17,18,19,255,255,255,255,255},
 {0,1,2,3,5,6,16,17,18,19,20,255},
 {0,1,16,17,18,19,255,255,255,255,255,255},
 {5,12,13,17,18,19,255,255,255,255,255,255},
 {2,3,12,13,255,255,255,255,255,255,255,255},
 {8,9,10,11,12,13,255,255,255,255,255,255},
 {2,3,9,10,11,255,255,255,255,255,255,255},
 {2,16,17,18,19,255,255,255,255,255,255,255},
 {2,5,9,10,20,21,255,255,255,255,255,255},
 {255,255,255,255,255,255,255,255,255,255,255,255},
};

// only upper case
// space = [
const int textlength = 43;
char displayText[textlength+1] = "THE[QUICK[BROWN[FOX[JUMPS[OVER[THE[LAZY[DOG";
Pixelgroup activeGroup(0);


void alphabetSetter(int letternumber){
  // copy group and fadeout?
  
  activeGroup.setRGB(0, 0, 0);
  writeGroups();
  activeGroup.clear();
  
  for (int i=0;i<12;i++){
    if (alphabetSoup[letternumber-65][i] != 255){
      for (int j=0;j<11;j++){
        int ledNumber = segments[alphabetSoup[letternumber-65][i]][j];
        
        if (ledNumber < 255){
          Serial.println(ledNumber);          
          activeGroup.addPixel(ledNumber);
        }
      }
    }
    Serial.println("-----------");
  }
  
    

  
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
  activeGroup.paint(pixelWriter);
  pixelWriter.show();  
}



void setup()
{
  Serial.begin(9600); 
 
  segmentHelper(0,40,10);
  segmentHelper(1,50,10);
  segmentHelper(2,60,11);
  segmentHelper(3,71,9);
  segmentHelper(4,80,4);
  segmentHelper(5,84,9);
  segmentHelper(6,99,7);
  segmentHelper(7,106,11);
  segmentHelper(8,117,11);
  segmentHelper(9,128,7);  
  segmentHelper(10,134,4);
  segmentHelper(11,139,5);
  segmentHelper(12,144,6);
  segmentHelper(13,150,4);
  segmentHelper(14,154,8);
  segmentHelper(15,162,3);
  segmentHelper(16,165,9);  
  segmentHelper(17,173,5);
  segmentHelper(18,179,3);
  segmentHelper(19,183,3);
  segmentHelper(20,93,6);
  segmentHelper(21,70,5);
 
 
 
 // test all segments

  for (int i = 0; i<=22;i++){
    for (int j = 0; j <11;j++){
        Serial.println(i);
        Serial.println("*******");
        int ledNumber = segments[i][j];
          if (ledNumber < 255){
            Serial.print(ledNumber);
            Serial.print(", ");          
            activeGroup.addPixel(ledNumber);
          }
        }
    activeGroup.setRGB(155, 50, 50);
    writeGroups();
  
    delay(10);  
    activeGroup.setRGB(0, 0, 0);
    writeGroups();
    activeGroup.clear();    
  }
 
 
 
  strip.begin();
 
  pixelWriter.setShowFunc(showPixels);
 


  //------------------------
  // manipulate group
  // demonstrate available functions
  
    // set pixels
  // argument 1: amount of pixels (e.g.: 4)
  // argument 2..n: pixel indices (e.g.: 4, 5, 6, 7)
  
 
  
  //------------------------
  // set some colors, write them out


  
//  //------------------------
//  // setup fading of group thegroup
//  thegroup.setFrom(255, 0, 0);
//  thegroup.setTo(0, 0, 255);
//  thegroup.setLoop(EASING_LOOP_BOUNCE);
//  thegroup.setDuration(3000);
//  thegroup.setEasing(true);
//
//
//  //------------------------
//  // set strobing of thatgroup
//  thegroup.setOnTime(600); // in ms
//  thegroup.setOffTimeSec(0.1); // or in sec
//  thegroup.setStrobing(true);
//
//  //------------------------
//  // flickering?
//  // randomly flickering pixels in group
//  // value defines flickersteps
//  // the higher the number, the longer it flickers
//  thegroup.setFlicker(20);
}


void loop()
{
  // need to tick each group for animations like fading, strobing, flickering...
  // tick pickelgroups with same timestamp (so the animations are in sync)
  unsigned long _now = millis();
  
  // tick this group with timestamp
  activeGroup.update(_now);
  
  for (int i = 0; i< textlength;i++){
    alphabetSetter(displayText[i]);
    activeGroup.setRGB(255, 0, 0);
    writeGroups();
    delay(1000);
  }




  
  delay(20);
}



