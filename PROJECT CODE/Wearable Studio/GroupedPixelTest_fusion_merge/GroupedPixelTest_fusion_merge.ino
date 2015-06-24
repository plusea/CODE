#include <Adafruit_NeoPixel.h>
#include <Pixelgroup.h>
#include <avr/power.h>

#define PIN 6
#define pot A1
#define buttonPin 14
#define envelope A0
#define gate 10
int envelopeValue;
int buttonState = 0;    // variable for reading the button status
int buttonPressed = 0;  // stores the state of the button (0=not pressed, 1=pressed)
int mode = 0;           // mode will store the current blinking mode (0 - 3)
//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 
int x = 0; // variable to be updated by the interrupt




Adafruit_NeoPixel strip = Adafruit_NeoPixel(186, PIN, NEO_GRB + NEO_KHZ800);
PixelWriter pixelWriter(strip.getPixels(), (uint8_t)strip.numPixels(), PXW_GRB);
byte segments[22][11];
void segmentHelper(int number,int start,int length){
  for (int i=0;i<=11;i++){
    if (i < length){
      segments[number][i] = start + i;
    } 
    else{
      segments[number][i]= 255;
    }
  } 
}

//a segment11c, segment10, segment9, segment8b
byte alphabetSoup [27][12]= {
  {
    10,11,12,13,14,17,18,19,255,255,255,255        }
  ,
  {
    3,5,11,13,14,17,18,19,255,255,255,255        }
  ,
  {
    5,14,17,18,19,255,255,255,255,255,255,255        }
  ,
  {
    9,16,17,18,19,20,255,255,255,255,255,255        }
  ,
  {
    0,5,14,16,17,18,19,255,255,255,255,255        }
  ,
  {
    0,255,14,16,17,18,19,255,255,255,255,255        }
  , 
  {
    0,1,2,11,13,14,21,255,255,255,255,255        }
  ,  // G
  {
    10,11,12,13,17,18,19,255,255,255,255,255        }
  ,
  {
    0,1,5,16,17,18,19,20,255,255,255,255        }
  ,
  {
    16,17,18,19,20,255,255,255,255,255,255,255        }
  ,
  {
    3,10,11,17,18,19,255,255,255,255,255,255        }
  ,  // K
  {
    5,15,16,17,18,19,255,255,255,255,255,255        }
  ,
  {
    7,8,9,19,255,255,255,255,255,255,255,255        }
  ,
  {
    3,12,13,18,19,255,255,255,255,255,255,255        }
  ,
  {
    5,12,13,14,17,18,19,255,255,255,255,255        }
  ,
  {
    10,11,13,14,17,18,19,255,255,255,255,255        }
  ,
  {
    4,11,12,13,14,17,21,255,255,255,255,255        }
  , // Q
  {
    3,11,13,14,17,18,19,255,255,255,255,255        }
  ,
  {
    0,1,2,3,5,6,20,255,255,255,255,255        }
  ,
  {
    0,1,16,17,18,19,255,255,255,255,255,255        }
  ,
  {
    5,12,13,17,18,19,255,255,255,255,255,255        }
  ,
  {
    2,3,12,13,255,255,255,255,255,255,255,255        }
  ,
  {
    8,9,10,11,12,13,255,255,255,255,255,255        }
  , // W
  {
    2,3,9,10,11,255,255,255,255,255,255,255        }
  ,
  {
    2,16,17,18,19,255,255,255,255,255,255,255        }
  ,
  {
    2,5,9,10,20,21,255,255,255,255,255,255        }
  ,
  {
    255,255,255,255,255,255,255,255,255,255,255,255        }
  ,
};


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



// only upper case
// space = [
const int textlength = 43;
char displayText[textlength+1] = "THE[QUICK[BROWN[FOX[JUMPS[OVER[THE[LAZY[DOG";

const int triangleTextLength = 32;
char triangleText[triangleTextLength+1] = "TRIANGLES[ARE[MY[FAVORITE[SHAPE[";

const int donauTextLength = 43;
char donauText[donauTextLength+1] = "DONAUDAMPFSCHIFFFAHRTSGESELLSCHAFTSKAPITAEN";

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




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void setup() {
  pinMode(pot, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(envelope, INPUT_PULLUP);
  pinMode(gate, INPUT_PULLUP);
  //enable interrupt 0 which uses pin 2
  //jump to the increment function on falling edge
  attachInterrupt(0, increment, FALLING);
  //pinMode(buttonPin, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //ABC segments:
  segmentHelper(0,30,10);
  segmentHelper(1,40,10);
  segmentHelper(2,50,11);
  segmentHelper(3,61,9);
  segmentHelper(4,70,4);
  segmentHelper(5,74,9);
  segmentHelper(6,89,7);
  segmentHelper(7,96,11);
  segmentHelper(8,107,11);
  segmentHelper(9,118,7);  
  segmentHelper(10,124,4);
  segmentHelper(11,129,5);
  segmentHelper(12,134,6);
  segmentHelper(13,140,4);
  segmentHelper(14,144,8);
  segmentHelper(15,152,3);
  segmentHelper(16,155,9);  
  segmentHelper(17,163,5);
  segmentHelper(18,169,3);
  segmentHelper(19,173,3);
  segmentHelper(20,83,6);
  segmentHelper(21,60,5);
  strip.begin();
  pixelWriter.setShowFunc(showPixels);
}



// Interrupt service routine for interrupt 0
void increment() {
  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > 250)
  {
    mode++;
    if(mode>15) mode=0;
    last_button_time = button_time;
    Serial.println(mode); //print x to serial monitor

  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {
  int potValue = analogRead(pot);
  int maxBright = 30;
  potValue=map(potValue, 0, 1023, 0, 100);

  // MODES //
  if(mode == 0) {
    allOneColour(strip.Color(0,0,0)); // off
    for(uint16_t i=0; i<30; i++) {
      strip.setPixelColor(i, strip.Color(maxBright,maxBright,maxBright));
    }
    strip.show();
  }
  if(mode == 1) {
    allOneColour(strip.Color(0,0,0)); // off
  }
  //yellow line mode
  if(mode == 2) {
    colorWipe(strip.Color(30, 30, 0), 5); // yellow
    colorWipe(strip.Color(0, 0, 0), 5); // off
  }
  if(mode == 3) {
    colorWipe(strip.Color(random(maxBright),random(maxBright),random(maxBright)), 20); // random colour
    //colorWipe(strip.Color(0, 0, 0), 5); // off
  }
  if(mode == 4) {
    theaterChase(strip.Color(maxBright, maxBright, maxBright), 50); // White
  }
  if(mode == 5) {
    theaterChase(strip.Color(random(maxBright),random(maxBright),random(maxBright)), 50); // random colour
  }
  if(mode == 6) {
    if(digitalRead(gate) == 1) {
      oneRandom();
      delay(500);
      allOneColour(strip.Color(0,0,0)); // off
      delay(10);
    }
  }
  if(mode == 7) {
    if(digitalRead(gate) == 1) {  
      //envelopeValue = analogRead(envelope);
      //envelopeValue=map(envelopeValue, 0, 100, 0, 255 );
      //Serial.println(envelopeValue);
      randomPixels(strip.Color(random(maxBright),random(maxBright),random(maxBright)), random(30));
    }
    else {
      allOneColour(strip.Color(0,0,0)); // off
    }
  }
  if(mode == 8) {
    if(digitalRead(gate) == 1) { 
      randomPixels(strip.Color(random(maxBright/2),random(maxBright/3),random(maxBright/4)), random(10));
      delay(50);
      allOneColour(strip.Color(0,0,0)); // off
    }
  }
    if(mode == 9) {
    if(digitalRead(gate) == 1) { 
      randomPixels(strip.Color(70,0,0), random(10));
      delay(50);
      allOneColour(strip.Color(0,0,0)); // off
    }
  }
  //random colours
  if(mode == 10) {
    randomPixels(strip.Color(random(maxBright),random(maxBright),random(maxBright)), random(30));
    delay(50);
    allOneColour(strip.Color(0,0,0)); // off
  }

  //all segments random
  if(mode == 11) {
    allRandom();
    delay(2000);
    allOneColour(strip.Color(0,0,0)); // off
    delay(10);
  }
  //all segments random
  if(mode == 12) {
    oneRandom();
    delay(300);
    allOneColour(strip.Color(0,0,0)); // off
    delay(10);
  }

  //TEXT
  if(mode == 13) {
    allOneColour(strip.Color(0,0,0)); // off
    unsigned long _now = millis();  // need to tick each group for animations like fading, strobing, flickering...
    activeGroup.update(_now);    // tick this group with timestamp
    for (int i = 0; i< triangleTextLength;i++){
      if(mode == 13) {
        alphabetSetter(triangleText[i]);
        activeGroup.setRGB(5, 60, 10);
        writeGroups();
        delay(1000);
      }
    }
    delay(20);
  }
  //TEXT
  if(mode == 14) {
    allOneColour(strip.Color(0,0,0)); // off
    unsigned long _now = millis();  // need to tick each group for animations like fading, strobing, flickering...
    activeGroup.update(_now);    // tick this group with timestamp
    for (int i = 0; i< donauTextLength;i++){
      if(mode == 14) {
        alphabetSetter(donauText[i]);
        activeGroup.setRGB(3, 50, 30);
        writeGroups();
        delay(1000);
      }
    }
    delay(20);
  }
  //TEXT
  if(mode == 15) {
    allOneColour(strip.Color(0,0,0)); // off
    unsigned long _now = millis();  // need to tick each group for animations like fading, strobing, flickering...
    activeGroup.update(_now);    // tick this group with timestamp
    for (int i = 0; i< textlength;i++){
      if(mode == 15) {
        alphabetSetter(displayText[i]);
        activeGroup.setRGB(50, 50, 0);
        writeGroups();
        delay(1000);
      }
    }
    delay(20);
  }


  //    rainbowCycle(20);
  //    rainbow(20);
  //    theaterChaseRainbow(50);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// random pixels
void randomPixels(uint32_t c, uint8_t numPixs) {
  for(uint16_t i=0; i<numPixs; i++) {
    strip.setPixelColor(random(strip.numPixels()), c);
  }
  strip.show();
}


// Fill one colour
void allOneColour(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }

  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


void oneRandom(){
  int randomMax = 30;
  int randomPick = random(0,11);
  Serial.println(randomPick);
  if(randomPick==0) segment0.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==1) segment1.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==2) segment2.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==3) segment3.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==4) segment4.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==5) segment5.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==6) segment6.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==7) segment7.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==8) segment8.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==9) segment9.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==10) segment10.setRGB(random(randomMax), random(randomMax), random(randomMax));
  if(randomPick==11) segment11.setRGB(random(randomMax), random(randomMax), random(randomMax));
  writeSegmentGroups();
}


void allRandom(){
  int randomMax = 30;
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
  writeSegmentGroups();
}

void writeSegmentGroups()
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






