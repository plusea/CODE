/*
 Code based on Tom Igoe's Serial Graphing Sketch
 >> http://wiki.processing.org/w/Tom_Igoe_Interview
 
 Reads analog inputs and visualizes them by drawing a grid to represent location
 and using grayscale shading of each square to represent pressure value
 >> http://howtogetwhatyouwant.at/
 */

import processing.serial.*;

Serial myPort;  // The serial port
int maxNumberOfSensors = 36;     
float[] sensorValue = new float[maxNumberOfSensors];  // global variable for storing mapped sensor values
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int rows = 6;
int cols = 6;
int rectSize = 600/6;
int averageMIN = 150;
int averageMAX = 300;

void setup () { 
  size(600, 600);  // set up the window to whatever size you want
  println(Serial.list());  // List all the available serial ports
  String portName = Serial.list()[5];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  myPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte
  background(255);    // set inital background
  smooth();  // turn on antialiasing
  rectMode(CORNER);
}


void draw () {

  for (int r=0; r<rows; r++) {
    
    for (int c=0; c<cols; c++) {
      fill(sensorValue[(c*rows) + r]);
      rect(r*rectSize, c*rectSize, rectSize, rectSize);
    } // end for cols
  
} // end for rows

}


void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');  // get the ASCII string

  if (inString != null) {  // if it's not empty
    inString = trim(inString);  // trim off any whitespace
    int incomingValues[] = int(split(inString, ","));  // convert to an array of ints

    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      for (int i = 0; i < incomingValues.length; i++) {
        // map the incoming values (0 to  1023) to an appropriate gray-scale range (0-255):
        sensorValue[i] = map(incomingValues[i], averageMIN, averageMAX, 0, 255);
        //println(sensorValue[i]);

      }
    }
  }
}

