/*
  Based on Serial Graphing Sketch by Tom Igoe
 Language: Processing
 */

import processing.serial.*;
Serial myPort; 

int maxNumberOfSensors = 8;       // Arduino has 6 analog inputs, so I chose 6
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
float[] previousLin = new float[maxNumberOfSensors];  // array of previous values
float xpos = 0;                     // x position of the graph
int time = millis();
color graphColor = color(0,0,0);
int colorCount = 0;

boolean fontInitialized = false;  // whether the font's been initialized                   // The serial port
PFont myFont;  // font for writing text to the window

void setup () {
  size(1600, 1000);  // set up the window to whatever size you want:
  // List all the available serial ports:
  //println(Serial.list());
  printArray(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino or Wiring module, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  String portName = Serial.list()[7];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  // don't generate a serialEvent() until you get a newline (\n) byte:
  myPort.bufferUntil('\n');

  // create a font with the fourth font available to the system:
  myFont = loadFont("Serif-12.vlw"); 
  textFont(myFont,12);

  smooth();
  rectMode(CORNER);
  
  background(255);
  grid();
}


void draw () {
  // nothing happens in the draw loop, 
  // but it's needed to keep the program running

}


// if spacebar pressed then take a screenshot of window and save to code file:
void keyPressed(){
  if (key==' ') saveFrame();
}


