/*
  Based on Serial Graphing Sketch by Tom Igoe
  Language: Processing
*/

import processing.serial.*;

int maxNumberOfSensors = 800;
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

int rows = 28;
int cols = 28;
int[][] rSkinArray = new int[rows][cols+1]; // adding +1 to the cols accounts for the row number

int[] skinRef = {1,2,3}; // re-maps incoming values to their location on the skin -- ROWS

// re-maps incoming values to their location on the skin -- COLS
                 //{00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27}; 
int[] fleshRef = {0,6,1,3,2,4,5,26,25,24,23,7,8,9,10,11,12,13,14,15,16,27,17,18,20,19,21,22}; 

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
  myFont = loadFont("Serif-12.vlw"); 
  textFont(myFont,12);

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
