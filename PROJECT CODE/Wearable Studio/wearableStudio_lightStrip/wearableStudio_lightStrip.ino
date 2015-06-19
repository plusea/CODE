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
Adafruit_NeoPixel pixels = Adafruit_NeoPixel((NUMredPIXELS + NUMwhitePIXELS), LEDPIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;
int redBRIGHT = 100;
int whiteBRIGHT = 100;

void setup() {
  pinMode(BUTTONPIN, INPUT_PULLUP);
  pinMode(SPEAKERPIN, INPUT_PULLUP);

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
}

void loop() {
  boolean buttonSTATE = digitalRead(BUTTONPIN);
  Serial.println(analogRead(SPEAKERPIN));
  
  if(buttonSTATE == 0) {
    mode += 1;
    if(mode >= 2)mode=0;
  }



  if(mode == 0) {
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

    for(int i=0;i<NUMwhitePIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(whiteBRIGHT,whiteBRIGHT,whiteBRIGHT)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }

    for(int i=6;i<NUMPIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(redBRIGHT,0,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    }

    for(int i=5;i<NUMPIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    }

    for(int i=0;i<NUMPIXELS-NUMwhitePIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(NUMPIXELS-i, pixels.Color(redBRIGHT,0,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    }

    for(int i=0;i<NUMPIXELS-NUMwhitePIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(NUMPIXELS-i, pixels.Color(0,0,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    }
  }
  if(mode==1) {
    for(int i=0;i<NUMPIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    }
  }

}


