// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2011-10-07 - initial release

/* ============================================
 I2Cdev device library code is placed under the MIT license
 Copyright (c) 2011 Jeff Rowberg
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ===============================================
 */

// how to connect arduino with sensor: http://wiki.dxarts.washington.edu/groups/general/wiki/1b074/
//VCC 	3.3V
//GND 	GND
//SDA 	A4
//SCL 	A5

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"


// LED stuff::::
#include <SPI.h>
#include "fix_fft.h"

#define NUM 50
#define TRESHOLD 1000 //Schranke für auslöser - ein kleinerer Wert erhöht die Sensibilität
#define INTERVAL 50 //alle 50 Millisekunden messen, Wert muss evtl angepasst werden um bessere Ergebnisse zu erzielen

typedef struct color
{
  byte r, g, b;
}
color;

color pixels[NUM];

char im[128];
char data[128]; 

int moo=0;
int audio_in=3;

long framecount = 0;


struct color colorOFF = { 
  1,1,1 };

struct color colorON = { 
  255, 255, 255 };

struct color colorRed = { 
  255, 1, 1 };

struct color colorYellow = { 
  255, 255, 1 };

struct color colorTurquoise = { 
  1, 255, 255 };

struct color colorPurple = { 
  255, 1, 255 };

int input;




// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

//#define LED_PIN 13
//bool blinkState = false;



void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(38400);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // configure Arduino LED for
  //pinMode(LED_PIN, OUTPUT);

  // LED stuff::::
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  // SPI.setClockDivider(SPI_CLOCK_DIV16);  // 1 MHz
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // 2 MHz
  
}


int brightness = 2;

void loop() {
  acelero();
  
  //printAll();

  
  show2((byte *)pixels, sizeof(pixels));
}




void show2(byte *bytes, int size)
{
  for (int index=0; index<size; index++)
  {
    // nur 25% Helligkeit    
    byte c = bytes[index] >> brightness;

    for (SPDR = c; !(SPSR & _BV(SPIF)););
  }
}




