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

float scaleValue;
float probeValue;

int maxNumberOfSensors = 2;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window

void setup () {
  size(800, 600);        
  println(Serial.list());
  //printArray(Serial.list());
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  // don't generate a serialEvent() until you get a newline (\n) byte:
  myPort.bufferUntil('\n');
  // create a font with the fourth font available to the system:
  myFont = createFont(PFont.list()[3], 24);
  textFont(myFont);
  fontInitialized = true;
  // set inital background:
  background(0);
  // turn on antialiasing:
  smooth();
  strokeWeight(5);
}

void draw () {
  // nothing happens in the draw loop, 
  // but it's needed to keep the program running
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  // if it's not empty:
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);

    // convert to an array of ints:
    int incomingValues[] = int(split(inString, ","));

    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {

      for (int i = 0; i < incomingValues.length; i++) {

        if (i==0) {
          // PROBE //      
          probeValue = map(incomingValues[1], 0, 1023, 0, height-60);
          float oldProbeValue = probeValue;
          stroke(0, 0, 255);

          line(xpos, oldProbeValue, xpos+1, probeValue);
        }

        if (i==0) {
          // SCALE //
          scaleValue = map(incomingValues[0], 0, 1023, 0, height-60);
          float oldScaleValue = scaleValue;
          stroke(255, 0, 0);
          line(xpos, scaleValue, xpos+1, oldScaleValue);
        }
      }

        // refresh text background
        noStroke();
        fill(0);
        line(0, height-60, width, height-60);
        rect(0, height-60, width, height);

        fill(0, 0, 255);
        text("Probe:" + probeValue + "Ohm", 20, height-20);
        fill(255, 0, 0);
        text("Scale:" + scaleValue + "Grams", 20, height-40);

      // if you've drawn to the edge of the window, start at the beginning again:
      if (xpos >= width) {
        xpos = 0;
        background(0);
      } 
      else {
        xpos++;
      }
    }
  }
}

