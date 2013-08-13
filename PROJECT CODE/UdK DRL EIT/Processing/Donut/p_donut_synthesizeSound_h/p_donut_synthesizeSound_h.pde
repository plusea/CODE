///////////////////////////////////////
// sound code for donut
// press S to see sound wave graph 
// press G to see sensor data graph
///////////////////////////////////////

import processing.serial.*;

// import everything necessary to make sound.
import ddf.minim.*;
import ddf.minim.signals.*;

// create all of the variables that will need to be accessed in
// more than one methods (setup(), draw(), stop()).
Minim minim;
AudioOutput out;
SineWave sine;
SineWave sine2;
SineWave sine3;


int maxNumberOfSensors = 6;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port
char mode = 's';
float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int[] globalValues = new int[maxNumberOfSensors];  // array of previous values
int xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window


//// !!! Adjust MINs and MAXs to correspond to your sensor ranges !!! ///////
int minValue = 0;
int maxValue = 500;
int minValue2 = 0;
int maxValue2 = 500;
int minValue3 = 0;
int maxValue3 = 500;



void setup () {
  // set up the window to whatever size you want:
  //size(displayWidth, displayHeight);
  size(800, 600);        
  // List all the available serial ports:
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino or Wiring module, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  String portName = Serial.list()[4];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  // don't generate a serialEvent() until you get a newline (\n) byte:
  myPort.bufferUntil('\n');
  // create a font with the fourth font available to the system:
  myFont = createFont(PFont.list()[3], 14);
  textFont(myFont);
  fontInitialized = true;
  // set inital background:
  background(215);
  // turn on antialiasing:
  smooth();
  strokeWeight(10);
  myPort.write(maxNumberOfSensors);
  myPort.write('N');

  minim = new Minim(this);
  // get a line out from Minim, default bufferSize is 1024, default samplerate is 44100, bit depth is 16
  out = minim.getLineOut(Minim.STEREO);
  // create a sine wave Oscillator, set to 440 Hz, at 0.5 amplitude,sample rate from line out
  sine = new SineWave(440, 0.5, out.sampleRate());
  sine2 = new SineWave(1000, 0.5, out.sampleRate());
  sine3 = new SineWave(2000, 0.5, out.sampleRate());
  // set the portamento speed on the oscillator to 200 milliseconds
  sine.portamento(200);
  sine2.portamento(200);
  sine3.portamento(200);
  // add the oscillator to the line out
  out.addSignal(sine);
  out.addSignal(sine2);
  out.addSignal(sine3);
}



void draw () {
  generateSound();

  if (mode == 'g') sensorGraph();
  if (mode == 's') soundGraph();
}


void generateSound()
{
  // with portamento on the frequency will change smoothly

  ////// SINE WAVE //////
  float freq = constrain(globalValues[0], minValue, maxValue);
  freq = map(freq, minValue, maxValue, 1500, 60);
  sine.setFreq(freq);

  ////// SINE WAVE 2 //////
  float freq2 = constrain(globalValues[1], minValue2, maxValue2);
  freq2 = map(freq2, minValue2, maxValue2, 1500, 60);
  sine2.setFreq(freq2);
  
  ////// SINE WAVE 3 //////
  float freq3 = constrain(globalValues[2], minValue3, maxValue3);
  freq3 = map(freq3, minValue3, maxValue3, 1500, 60);
  sine3.setFreq(freq3);
  
  // pan always changes smoothly to avoid crackles getting into the signal
  // note that we could call setPan on out, instead of on sine
  // this would sound the same, but the waveforms in out would not reflectthe panning
  float pan = 0; //map(mouseX, 0, width, -1, 1);
  sine.setPan(pan);
}



void keyPressed() {
  background(0);
  if (key == 'G' || key == 'g') mode = 'g';
  if (key == 'S' || key == 's') mode = 's';
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  // if it's not empty:
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);

    // convert to an array of ints:
    int incomingValues[] = int(split(inString, ","));

    for (int i=0; i<incomingValues.length;i++) globalValues[i] = incomingValues[i];

    println(globalValues[0]);

    // print out the values
    //  print("length: " + incomingValues.length + " values.\t");
    //if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
    //graph();
    //}
  }
}


void stop()
{
  out.close();
  minim.stop();

  super.stop();
}

