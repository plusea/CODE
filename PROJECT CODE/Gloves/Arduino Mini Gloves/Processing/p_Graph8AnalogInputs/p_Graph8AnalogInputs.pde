
/*
Code based on Tom Igoe's Serial Graphing Sketch
 >> http://processing.org/exhibition/features/igoe/
 
 Reads analog inputs and sends them as a series of strings seperated with commas,
 and carriage returns after each full set of sensor values.
 >> http://www.kobakant.at/DIY/?cat=347
 */

import processing.serial.*;

int maxNumberOfSensors = 8;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
float xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window
int fingers = 5;


void setup () {
  size(1000, 700);        
  println(Serial.list());
  
  //USB:
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 115200);
  
  //Bluetoth:
  //myPort = new Serial(this, "/dev/tty.RN42-45ED-SPP-1", 115200);
  //myPort = new Serial(this, "/dev/cu.RN42-45ED-SPP-1", 115200);
  //myPort = new Serial(this, "/dev/cu.00-06-66-43-45-ed-SPP", 115200);
  
  myPort.clear();
  myPort.bufferUntil('\n');
  myFont = createFont(PFont.list()[3], 14);
  textFont(myFont);
  fontInitialized = true;
  background(255);
  smooth();
}



void draw () {
  
}



void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  background(255);
  // if it's not empty:

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);


    // convert to an array of ints:
    int incomingValues[] = int(split(inString, ","));
    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      for (int i = 0; i < incomingValues.length; i++) {

        incomingValues[i] = int(map(incomingValues[i], 0, 1023, 0, height));
        incomingValues[i] = height - incomingValues[i];
        println(incomingValues[0]);
      }

      //thumb:
      fill(165,10,200);
      rect(width-width/fingers, height, width/fingers, -incomingValues[0]);


      //index
      fill(165,10,200);
      rect(width-2*width/fingers, height, width/fingers, -incomingValues[1]);

      fill(255, 255, 0);
      rect(width-2*width/fingers, height-incomingValues[1], width/fingers, -incomingValues[2]);


      //middle
      fill(165,10,200);
      rect(width-3*width/fingers, height, width/fingers, -incomingValues[3]);

      fill(255, 255, 0);
      rect(width-3*width/fingers, height-incomingValues[3], width/fingers, -incomingValues[4]);


      //ring
      fill(165,10,200);
      rect(width-4*width/fingers, height, width/fingers, -incomingValues[5]);

      fill(255, 255, 0);
      rect(width-4*width/fingers, height-incomingValues[5], width/fingers, -incomingValues[6]);


      //little
      fill(165,10,200);
      rect(width-5*width/fingers, height, width/fingers, -incomingValues[7]);
    }
  }
}







void keyPressed() {
  if (key==' ')
    saveFrame();
}

