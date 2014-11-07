/*
  OSC_illoscope.pde
  Author: Seb Madgwick

  OSC-illoscope for plotting analogue input channels of x-OSC.  Requires oscP5
  library. See: http://www.sojamo.de/libraries/oscP5/

  Tested with Processing 2.0.1 and oscP5 0.9.8
*/

import oscP5.*;

//int[] selectedChannels = { 1 };
//int[] selectedChannels = { 1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16 };
//int[] selectedChannels = { 14, 15, 16 };
int[] selectedChannels = { 1, 5, 6, 7, 8, 9, 10, 11, 12 };
//int[] selectedChannels = { 6, 7};

OscP5 oscP5;
float[] analogInputs = new float[16];
float[] previousYPos = new float[selectedChannels.length];
float xPos = 0;
int previousWidth, previousHeigth;  // used to detect window resize

void setup() {
  oscP5 = new OscP5(this, 8000);  // listen to port 8000
  size(1600, 1000);
  if (frame != null) {
    frame.setResizable(true);
  }
  drawBackground();
}

void draw() {

  // Trace analogue input values
  strokeWeight(3);  // trace width
  //stroke(2,26,144); // polyester - old
  stroke(216,4,82); // polyimide - new
  for (int i = 0; i < selectedChannels.length; i++) {
    if(i==0) stroke(116,178,4); // button
    else stroke(216,4,82); // polyimide - new
    float graphHeight = height / selectedChannels.length;
    float yPos = map(analogInputs[selectedChannels[i] - 1], 0, 1, i * graphHeight + graphHeight, i * graphHeight);
    line(xPos, previousYPos[i], xPos+1, yPos);
    previousYPos[i] = yPos;
  }

  // Restart if graph full or window resized
  if (++xPos >= width || previousWidth != width || previousHeigth != height) {
    saveFrame();
    previousWidth = width;
    previousHeigth = height;
    xPos = 0;
    drawBackground();
  }
}

void drawBackground() {
  strokeWeight(1);                          // rectangle border width
  PFont f = createFont("Arial", 16, true);  // Arial, 16 point, anti-aliasing on
  for (int i = 0; i < selectedChannels.length; i++) {
    float graphHeight = height / selectedChannels.length;

    // Different rectangle border and fill colour for alternate graphs
    if(i % 2 == 0) {
      stroke(0);
      fill(255);
    }
    else {
      stroke(0);
      fill(255);
    }
    rect(0, i * graphHeight, width, graphHeight);

    // Print channel number
    fill(64);
    textFont(f, (int)graphHeight);
    text(nf(selectedChannels[i], 1), 10, (i + 1) * graphHeight);
  }
}

void oscEvent(OscMessage theOscMessage) {
  String addrPattern = theOscMessage.addrPattern();

  // Print address pattern to terminal
  println(addrPattern);

  // Analogue input values
  if (addrPattern.equals("/inputs/analogue")) {
    for(int i = 0; i < analogInputs.length; i ++) {
      analogInputs[i] = theOscMessage.get(i).floatValue();
    }
  }
}

void keyPressed(){
  if (key==' ')
    saveFrame();
}
