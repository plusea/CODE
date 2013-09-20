/*
  Reads in capacitive values from lilypad and visualizest
 Based on Serial Graphing Sketch by Tom Igoe
 and Minim TriggerSample example
 */

import processing.serial.*;
import ddf.minim.*;

int maxNumberOfSensors = 4;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port
int[] sensorValues = new int[maxNumberOfSensors];  // array of previous values
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window

Minim minim;
AudioSample kick;
AudioSample snare;
AudioSample bass;
AudioSample cymbal;



void setup () {
  size(displayWidth, displayHeight);
  //size(800, 600, P3D);        
  println(Serial.list());
  String portName = Serial.list()[5];
  myPort = new Serial(this, "COM17", 57600);
  myPort.clear();
  myPort.bufferUntil('\n');
  myFont = createFont(PFont.list()[3], 14);
  textFont(myFont);
  fontInitialized = true;
  background(0);
  smooth();

  minim = new Minim(this);
  kick = minim.loadSample( "BD.mp3", 512);
  snare = minim.loadSample("SD.wav", 512);
  bass = minim.loadSample("bass_single.wav", 512);
  cymbal = minim.loadSample("cymbal_single.wav", 512);
}

void draw () {
  //graph();
  circle();
  sound();
}


