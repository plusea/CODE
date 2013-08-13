import processing.serial.*;

// import everything necessary to make sound.
import ddf.minim.*;
import ddf.minim.ugens.*;

// create all of the variables that will need to be accessed in
// more than one methods (setup(), draw(), stop()).
Minim minim;
AudioOutput out;

// the Oscil we use for modulating frequency.
Oscil fm;

int maxNumberOfSensors = 6;       // Arduino has 6 analog inputs, so I chose 6
boolean fontInitialized = false;  // whether the font's been initialized
Serial myPort;                    // The serial port

char mode = 's';

float[] previousValue = new float[maxNumberOfSensors];  // array of previous values
int[] globalValues = new int[maxNumberOfSensors];  // array of previous values
int xpos = 0;                     // x position of the graph
PFont myFont;                     // font for writing text to the window




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

  // initialize the minim and out objects
  minim = new Minim( this );
  out   = minim.getLineOut();

  // make the Oscil we will hear.
  // arguments are frequency, amplitude, and waveform
  Oscil wave = new Oscil( 200, 0.8, Waves.TRIANGLE );
  // make the Oscil we will use to modulate the frequency of wave.
  // the frequency of this Oscil will determine how quickly the
  // frequency of wave changes and the amplitude determines how much.
  // since we are using the output of fm directly to set the frequency 
  // of wave, you can think of the amplitude as being expressed in Hz.
  fm   = new Oscil( 10, 2, Waves.SINE );
  // set the offset of fm so that it generates values centered around 200 Hz
  fm.offset.setLastValue( 200 );
  // patch it to the frequency of wave so it controls it
  fm.patch( wave.frequency );
  // and patch wave to the output
  wave.patch( out );
}



void draw () {
  generateSound();

  if (mode == 'g') sensorGraph();
  if (mode == 's') soundGraph();
}


void generateSound()
{
  float modulateAmount = map( mouseY, 0, height, 220, 1 );
  float modulateFrequency = map( globalValues[0], 15, 40, 0.1, 100 );

  println(modulateFrequency);

  fm.frequency.setLastValue( modulateFrequency );
  fm.amplitude.setLastValue( modulateAmount );
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

    //println(globalValues[0]);

    // print out the values
    //  print("length: " + incomingValues.length + " values.\t");
    //if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
    //graph();
    //}
  }
}

