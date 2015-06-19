/*
 Code based on Tom Igoe's Serial Graphing Sketch
 >> http://wiki.processing.org/w/Tom_Igoe_Interview
 
 Reads four analog inputs that represent the distance of contact from
 four corners of touchpad and visualizes the location by drawing
 circles from each corner
 */

import processing.serial.*;

Serial myPort;  // The serial port
int maxNumberOfSensors = 4;   
float[] sensorValues = new float[maxNumberOfSensors];
float sensorValueX;
float sensorValueY;
int scaleValue = 2;

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
  //noFill();
  fill(100,100,100,100);
  ellipse(0,0, scaleValue*sensorValues[0], scaleValue*sensorValues[0]);
  ellipse(0,width, scaleValue*sensorValues[1], scaleValue*sensorValues[1]);
  ellipse(height,width, scaleValue*sensorValues[2], scaleValue*sensorValues[2]);
  ellipse(height,0, scaleValue*sensorValues[3], scaleValue*sensorValues[3]);
//  ellipse(sensorValueY, sensorValueX, 10,10);
}


void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');  // get the ASCII string

  if (inString != null) {  // if it's not empty
    inString = trim(inString);  // trim off any whitespace
    int incomingValues[] = int(split(inString, ","));  // convert to an array of ints

    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      for (int i = 0; i < incomingValues.length; i++) {
        // map the incoming values (0 to  1023) to an appropriate gray-scale range (0-255):
        sensorValues[i] = map(incomingValues[i], 0, 1023, 0, width); 
      }
    }
  }
}

