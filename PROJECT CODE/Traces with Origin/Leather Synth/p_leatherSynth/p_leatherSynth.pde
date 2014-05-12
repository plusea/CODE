/*
 Reads in resistive values from lilypad and visualizes them
 Based on Serial Graphing Sketch by Tom Igoe
 and Minim TriggerSample example
 
 you'll probably have to adjust the portname or list number to connect to it. 
 you can press 'g' for graph and computer sounds and 'v' for visualization. 
 if ball is not connected to computer and you power with battery, then the on-board speaker will make sounds.
 */

import processing.serial.*;
import ddf.minim.*;

int maxNumberOfSensors = 3;       // Arduino has 6 analog inputs, so I chose 6
int sensorThreshold = 1010;
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port
int[] sensorValues = new int[maxNumberOfSensors];  // array of previous values
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window
char state = 'v';


Minim minim;
AudioSample kick;
AudioSample snare;
AudioSample bass;
AudioSample cymbal;
AudioSample hihat;
AudioSample kick2;



void setup () {
  //size(displayWidth, displayHeight);
  size(800, 600);        
  println(Serial.list());
  String portName = Serial.list()[4];
  //myPort = new Serial(this, "COM13", 9600);  //USB
  myPort = new Serial(this, portName, 9600);  //Bluetooth module
  myPort.clear();
  myPort.bufferUntil('\n');
  myFont = createFont(PFont.list()[0], 36);
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

  myPort.write('p');
}



void draw () {
  if (state=='g') {
    myPort.write('p');
    graph();
  }
  if (state=='v') {
    myPort.write('p');
    circle();
  }
  if (state=='s') {
    myPort.write('x');
  }
}


void keyPressed() {
  background(255);
  xpos=0;
  if (key == 'g')state = 'g';
  if (key == 'v')state = 'v';
  if (key == 's')state = 's';
  if (keyCode == UP)sensorThreshold+=10;
  if (keyCode == DOWN)sensorThreshold-=10;
}

