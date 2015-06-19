// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define LEDPIN 5
#define BUTTONPIN 6
#define SPEAKERPIN A0

int mode=0;

// How many NeoPixels are attached to the Arduino?
#define NUMredPIXELS 28
#define NUMwhitePIXELS 6
#define NUMPIXELS 34

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel((NUMredPIXELS + NUMwhitePIXELS), LEDPIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;
int redBRIGHT = 100;
int whiteBRIGHT = 100;

void setup() {
  pinMode(BUTTONPIN, INPUT_PULLUP);
  pinMode(SPEAKERPIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //Serial.begin(9600);
}

void loop() {
  boolean buttonSTATE = digitalRead(BUTTONPIN);
  int soundLevel = analogRead(SPEAKERPIN);
  int soundColour = map(soundLevel, 0, 100, 0, 255);
  soundLevel = map(soundLevel, 0, 100, 0, NUMPIXELS);
  //Serial.println(soundLevel);
  
  
  strip.setPixelColor(soundLevel, Wheel(soundColour)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware.

//  for(int i=0;i<NUMPIXELS;i++){
//  strip.setPixelColor(i, Wheel(0)); // Moderately bright green color.
//  strip.show(); // This sends the updated pixel color to the hardware.
//  }

}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



