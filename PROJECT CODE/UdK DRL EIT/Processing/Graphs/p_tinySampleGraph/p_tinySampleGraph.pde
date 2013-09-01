/*
visualizing sensor input from knit samples
using ATtiny interface circuit
DRL EIT project code
*/

import processing.serial.*;

int maxNumberOfSensors = 3;       // Arduino has 6 analog inputs, so I chose 6
Serial myPort;                    // The serial port
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window
int mode;
int[] globalValues = new int[3];



void setup () {
  size(1000, 600);        
  println(Serial.list());
  String portName = Serial.list()[4];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  myPort.bufferUntil('\n'); // don't generate a serialEvent() until you get a newline (\n) byte
  myFont = createFont(PFont.list()[3], 14);
  textFont(myFont);

  background(211);
  smooth();
}


void draw () {
  text("KNIT SAMPLE VISUALIZATION", 10, 10);
  if (mode == 'c') {
    capacitive();
    println(globalValues[0]);
  }

  if (mode == 'g') {
    graph();
  }
  
  if (mode == 'p') {
    play();
  }
}






