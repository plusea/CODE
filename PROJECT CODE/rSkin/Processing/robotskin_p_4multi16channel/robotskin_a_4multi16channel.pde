/*
  Based on Serial Graphing Sketch by Tom Igoe
  Language: Processing
*/

import processing.serial.*;

int maxNumberOfSensors = 800;//784;       //= 282*28
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
float xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window
 
void setup () {
  size(1600, 800);        // set up the window to whatever size you want:
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

  background(255);
  smooth();
}
 
void draw () {
  // nothing happens in the draw loop, 
  // but it's needed to keep the program running
}

void keyPressed(){
  if (key==' ')
    saveFrame();
}
