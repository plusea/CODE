/*
  Based on Serial Graphing Sketch by Tom Igoe
 Reads two analog sensor values and graphs them
 Thresholds for each sensor input, trigger colour changes in graph
 */

import processing.serial.*;

int maxNumberOfSensors = 3;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window
float ypos;

// TOP SENSOR
float topSensorMin = 0;
float topSensorMax = 1023;
//float topSensorThreshold = 400;

// BOTTOM SENSOR
float bottomSensorMin = 0;
float bottomSensorMax = 1023;
//float bottomSensorThreshold = 200;

void setup () {
  // set up the window to whatever size you want:
  size(1800, 1000);        
  //println(Serial.list());
  printArray(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino or Wiring module, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  String portName = Serial.list()[9];
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
      for (int i = 0; i < 2; i++) {

        // bottom sensor:
        if (i==0) ypos = map(incomingValues[i], bottomSensorMin, bottomSensorMax, 0, height/2);

        // top sensor:
        if (i==1) ypos = map(incomingValues[i], topSensorMin, topSensorMax, 0, height/2);

        // figure out the y position for this particular graph:
        float graphBottom = i * height/2;
        ypos = ypos + graphBottom;

        // make a black block to erase the previous text:
        noStroke();
        fill(255);
        rect(10, graphBottom+1, 110, 20);

        // print the sensor numbers to the screen:
        fill(0);
        int textPos = int(graphBottom) + 14;
        // sometimes serialEvent() can happen before setup() is done.
        // so you need to make sure the font is initialized before
        // you text():
        if (fontInitialized) {
          text("Sensor " + i + ":" + incomingValues[i], 10, textPos);
        }

        // draw a line at the bottom of each graph:
        stroke(0);
        line(0, graphBottom, width, graphBottom);
        // change colors to draw the graph line:
        //stroke(64*i, 32*i, 255);

        strokeWeight(5);
        stroke(0);

        if (i==0) {
          if (incomingValues[2] == 1 || incomingValues[2] == 3) stroke (255, 0, 0);
        }
        if (i==1) {
          if (incomingValues[2] == 2 || incomingValues[2] == 3) stroke (255, 0, 0);
        }
        if (incomingValues[2] == 4) stroke (0, 255, 0);

        line(xpos, previousValue[i], xpos+1, ypos);

        // save the current value to be the next time's previous value:
        previousValue[i] = ypos;
      }
    }
    // if you've drawn to the edge of the window, start at the beginning again:
    if (xpos >= width) {
      xpos = 0;
      background(255);
    } else {
      xpos++;
    }
  }
}

