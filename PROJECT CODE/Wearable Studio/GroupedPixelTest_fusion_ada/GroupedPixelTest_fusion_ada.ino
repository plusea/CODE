#include <Adafruit_NeoPixel.h>
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
}

// Interrupt service routine for interrupt 0
void increment() {
  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > 250)
  {
    mode++;
    if(mode>7) mode=0;
    last_button_time = button_time;
    Serial.println(mode); //print x to serial monitor
  }
}





void loop() {
  int potValue = analogRead(pot);
  int maxBright = 30;

  potValue=map(potValue, 0, 1023, 0, 100);

  // MODES //

  //yellow line mode
  if(mode == 5) {
    colorWipe(strip.Color(30, 30, 0), 5); // yellow
    colorWipe(strip.Color(0, 0, 0), 5); // off
  }
  if(mode == 1) {
    colorWipe(strip.Color(random(maxBright),random(maxBright),random(maxBright)), 20); // random colour
    //colorWipe(strip.Color(0, 0, 0), 5); // off
  }
  if(mode == 2) {
    theaterChase(strip.Color(maxBright, maxBright, maxBright), 50); // White
  }

  if(mode == 3) {
    theaterChase(strip.Color(random(maxBright),random(maxBright),random(maxBright)), 50); // random colour
  }

  if(mode == 4) {
    if(digitalRead(gate) == 1) {
      allOneColour(strip.Color(random(maxBright),random(maxBright),random(maxBright))); // random colour
    }
  }

  if(mode == 6) {


    if(digitalRead(gate) == 1) {  
      //envelopeValue = analogRead(envelope);
      //envelopeValue=map(envelopeValue, 0, 100, 0, 255 );
      //Serial.println(envelopeValue);
      allOneColour(strip.Color(50,0,0)); // random colour
      delay(100);

    }
    else {
      allOneColour(strip.Color(0,0,0)); // off
      delay(100);
    }
  }

  if(mode == 0) {
  randomPixels(strip.Color(random(maxBright),random(maxBright),random(maxBright)), random(30));
    delay(1000);
  allOneColour(strip.Color(0,0,0)); // off

  }

  //    rainbowCycle(20);
  //    rainbow(20);
  //    theaterChaseRainbow(50);
}


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



