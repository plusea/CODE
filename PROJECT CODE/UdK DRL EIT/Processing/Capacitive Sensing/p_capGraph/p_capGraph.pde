/*
  Reads in capacitive values from lilypad and visualizest
 Based on Serial Graphing Sketch by Tom Igoe
 and Minim TriggerSample example
 */

import processing.serial.*;
import ddf.minim.*;

int maxNumberOfSensors = 9;       // Arduino has 6 analog inputs, so I chose 6
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
AudioSample hihat;
AudioSample kick2;
AudioSample loosekick;
AudioSample loosekick2;



void setup () {
  size(displayWidth, displayHeight);
  //size(800, 600, P3D);        
  println(Serial.list());
  String portName = Serial.list()[4];
  myPort = new Serial(this, portName, 57600);
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
  hihat = minim.loadSample("hihat_single.wav", 512);
  kick2 = minim.loadSample("kick_single.wav", 512);
  loosekick = minim.loadSample("loosekick_single.wav", 512);
  loosekick2 = minim.loadSample("loosekick2_single.wav", 512);
  
  
  if ( kick == null ) println("Didn't get kick!");
  if ( snare == null ) println("Didn't get snare!");
  if ( snare == null ) println("Didn't get sample!");
}

void draw () {
  //graph();
  circle();
  sound();
}


