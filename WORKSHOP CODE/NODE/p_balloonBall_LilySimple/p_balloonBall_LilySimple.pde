/*
 Reads in capacitive values from lilypad and visualizes them
 Based on Serial Graphing Sketch by Tom Igoe
 and Minim TriggerSample example

 you'll probably have to adjust the portname or list number to connect to it. 
 you can press 'g' for graph and computer sounds and 'v' for visualization. 
 if ball is not connected to computer and you power with battery, then the on-board speaker will make sounds.
*/

import processing.serial.*;
import ddf.minim.*;

int maxNumberOfSensors = 3;       // Arduino has 6 analog inputs, so I chose 6
Serial myPort;                    // The serial port
int[] sensorValues = new int[maxNumberOfSensors];  // array of previous values
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values

Minim minim;
AudioSample kick;
AudioSample snare;
AudioSample bass;
AudioSample cymbal;
AudioSample hihat;
AudioSample kick2;



void setup () {
  //size(displayWidth, displayHeight);
  size(800, 600, P3D);        
  println(Serial.list());
  String portName = Serial.list()[11];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  myPort.bufferUntil('\n');

  minim = new Minim(this);
  kick = minim.loadSample( "BD.mp3", 512);
  snare = minim.loadSample("SD.wav", 512);
  bass = minim.loadSample("bass_single.wav", 512);
  cymbal = minim.loadSample("cymbal_single.wav", 512);
  hihat = minim.loadSample("hihat_single.wav", 512);
  kick2 = minim.loadSample("kick_single.wav", 512);
}


void draw () {
    if (sensorValues[0] < 800 && sensorValues[0] > 100) sound(0);
    if (sensorValues[0] < 100) sound(1);
    if (sensorValues[1] == 0) sound(2);
    if (sensorValues[2] == 0) sound(3);
}




