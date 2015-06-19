/*
 Code based on Tom Igoe's Serial Graphing Sketch
 >> http://wiki.processing.org/w/Tom_Igoe_Interview
 
 Reads two analog inputs that represent x and y axis of a touchpad
 and visualizes the location
 */

import processing.serial.*;

Serial myPort;  // The serial port
int maxNumberOfSensors = 2;     
float sensorValueX;
float sensorValueY;

void setup () { 
  size(600, 600);  // set up the window to whatever size you want
  println(Serial.list());  // List all the available serial ports
  String portName = Serial.list()[11];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  myPort.bufferUntil('\n');  // don't generate a serialEvent() until you get a newline (\n) byte
  background(255);    // set inital background
  smooth();  // turn on antialiasing
}


void draw () {
  background(255);
  strokeWeight(5);
  noFill();
  line(0, sensorValueX, height, sensorValueX);
  line(sensorValueY, 0, sensorValueY, width);
  ellipse(sensorValueY, sensorValueX, 20,20);
}


void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');  // get the ASCII string

  if (inString != null) {  // if it's not empty
    inString = trim(inString);  // trim off any whitespace
    int incomingValues[] = int(split(inString, ","));  // convert to an array of ints

    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      for (int i = 0; i < incomingValues.length; i++) {
        // map the incoming values (0 to  1023) to an appropriate gray-scale range (0-255):
        sensorValueX = map(incomingValues[0], 0, 1023, 0, width); 
        sensorValueY = map(incomingValues[1], 0, 1023, 0, height);
      }
    }
  }
}

