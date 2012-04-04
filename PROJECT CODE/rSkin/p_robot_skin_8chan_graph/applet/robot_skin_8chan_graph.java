import processing.core.*; 
import processing.xml.*; 

import processing.serial.*; 

import java.applet.*; 
import java.awt.*; 
import java.awt.image.*; 
import java.awt.event.*; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class robot_skin_8chan_graph extends PApplet {

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



int maxNumberOfSensors = 4;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
float xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window
 
public void setup () {
  // set up the window to whatever size you want:
  size(1000, 500);        
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
}
 
public void draw () {
  // nothing happens in the draw loop, 
  // but it's needed to keep the program running
}
public void grid(){
  for(int i=1; i<height; i+=height/(10*maxNumberOfSensors)){
   
strokeWeight(0.5f);
    line(0 , i , width , i);
  }
    for(int i=1; i<height; i+=height/(maxNumberOfSensors)){
   
strokeWeight(2);
    line(0 , i , width , i);
  }
  
}

public void keyPressed(){
  if (key==' ')
    saveFrame();
}
public void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  // if it's not empty:
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);

    // convert to an array of ints:
    int incomingValues[] = PApplet.parseInt(split(inString, ","));

    // print out the values
    //  print("length: " + incomingValues.length + " values.\t");
    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      for (int i = 0; i < incomingValues.length; i++) {

        // map the incoming values (0 to  1023) to an appropriate
        // graphing range (0 to window height/number of values):
        float ypos = map(incomingValues[i], 0, 1023, 0, height/incomingValues.length);

        // figure out the y position for this particular graph:
        float graphBottom = i * height/incomingValues.length;
        ypos = ypos + graphBottom;

        // make a black block to erase the previous text:
        noStroke();
        fill(255);
        //rect(10, graphBottom+1, 110, 20);

        // print the sensor numbers to the screen:
        fill(0);
        int textPos = PApplet.parseInt(graphBottom) + 14;
        // sometimes serialEvent() can happen before setup() is done.
        // so you need to make sure the font is initialized before
        // you text():
        if (fontInitialized) {
          //text("Sensor " + i + ":" + incomingValues[i], 10, textPos);
        }

        stroke(0);
        strokeWeight(5);
        line(xpos, height-previousValue[i], xpos+1, height-ypos);
        // save the current value to be the next time's previous value:
        previousValue[i] = ypos;
      }
    }
    // if you've drawn to the edge of the window, start at the beginning again:
    if (xpos >= width) {
      saveFrame();
      xpos = 0;
      background(255);
    } 
    else {
      xpos+=1;
    }
  }
}

  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#FFFFFF", "robot_skin_8chan_graph" });
  }
}
