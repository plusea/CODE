/*
  4 Step Sequencer!!!!
  Control pitch for each step + control BPM + tempo visualfeedback
 
  This example code is for educational purpose and it is in the public domain.
*/

// Tones table definition
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


// Declaration of tones used in the sequencer
int pitch[] = { 
                NOTE_C4,
                NOTE_D4,
                NOTE_E4,
                NOTE_F4,
                NOTE_G4,
                NOTE_A4,
                NOTE_B4,
                NOTE_C5 };
                
// Declaration of variables               
int speaker = 6;                          // Speaker output pin
int k;                                    // Variable to store the value of the loop    
int sensorRead;                           // Variable to store the value of the BPM potentiometer
// Variables used to calculate BPM
float bpm;
float conversion;
int interval;
int maxbpm = 1000;
int minbpm = 100;
// Arrays to define notes
int value[] = {0, 0, 0, 0};              //value to define the discrete interval of tune using the pot
int note[] = {0, 0, 0, 0};  
// Duration of notes for each step
int D[] = {100, 100, 100, 100};  
// Variables to drive LEDs
int ledPins[] = {2, 3, 4, 5};
int l;

void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);    
}


void loop() { 
  
  for (k = 0; k <= 3; k++) {                                 // Cycle on each pot
    //D[k] = map(analogRead(5), 0, 900, 10, 600);            // If you connect a sensor to Analog Input 5 you can control note duration
    value[k] = map(analogRead(k), 0, 1023, 0, 8000);         // Mapping the value of the Potentiometer to a frequency between 0 and 8000 Hz
    
    if ((value[k]>=0) && (value[k]<100))                     // Discretization of the pot intervals - in order to assign the note
      note[k] = 0;    
    if ((value[k]>=100) && (value[k]<1000))
      note[k] = pitch[0];
    if ((value[k]>=1000) && (value[k]<2000))
      note[k] = pitch[1];
    if ((value[k]>=2000) && (value[k]<3000))
      note[k] = pitch[2];
    if ((value[k]>=3000) && (value[k]<4000))
      note[k] = pitch[3];
    if ((value[k]>=4000) && (value[k]<5000))
      note[k] = pitch[4];
    if ((value[k]>=5000) && (value[k]<6000))
      note[k] = pitch[5];
    if ((value[k]>=6000) && (value[k]<7000))
      note[k] = pitch[6];
    if ((value[k]>=7000) && (value[k]<=8000))
      note[k] = pitch[7];      

    tone(speaker, note[k], D[k]);                             // Play the note

    // BPM stuff
    sensorRead = analogRead(4);                               // Read from Analog Input 4 to define BPM
    // Math for BPM conversion into milliseconds
    bpm = map(sensorRead, 0, 1023, minbpm, maxbpm);
    conversion = (1/(bpm/60))*1000;
    interval = int(conversion);  
    
    // turn On and Off the current LED at tempo defined with math above
    digitalWrite(ledPins[k], HIGH);
    delay(interval);
    digitalWrite(ledPins[k], LOW);
  }  
}
