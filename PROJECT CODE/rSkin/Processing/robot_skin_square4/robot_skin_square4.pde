/*
  Serial Graphing Sketch
  by Tom Igoe
  Language: Processing
 
  This sketch takes ASCII values from the serial port 
  at 9600 bps and graphs them.
  The values should be comma-delimited, with a newline 
  at the end of every set of values.
  The expected range of the values is between 0 and 1023.
 
  Created 20 April 2005
  Updated 27 June 2008
*/

import processing.serial.*;

int maxNumberOfSensors = 4;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
float[] previousTransferValue = new float[maxNumberOfSensors];  // array of previous values

float xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window

int xpo = 0;
int ypo = 0;

void setup () {
  // set up the window to whatever size you want:
  size(1600, 1000);        
  // List all the available serial ports:
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino or Wiring module, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  // don't generate a serialEvent() until you get a newline (\n) byte:
  myPort.bufferUntil('\n');
  // create a font with the fourth font available to the system:
  myFont = createFont(PFont.list()[3], 14);
  textFont(myFont);
  fontInitialized = true;
  // set inital background:
  background(255);
  // turn on antialiasing:
  smooth();
  grid();
}
 
void draw () {
  // nothing happens in the draw loop, 
  // but it's needed to keep the program running
}

