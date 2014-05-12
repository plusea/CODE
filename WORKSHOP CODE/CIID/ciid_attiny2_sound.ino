//                                       attiny85
//                                 reset -+---+- power
//    (analog input: discrete notes) pb3 -+*  +- pb2 (led output)
//  (analog input: continuous tones) pb4 -+   +- pb1 (not used)
//                                ground -+---+- pb0 (output: speaker)

int val;
long d, d2;
long freqs[21] = {
  2093, 2349, 2637, 2793, 3135,
  3520, 3951, 4186, 4698, 5274,
  5587, 6271, 7040, 7902, 8372,
  9397, 10548, 11175, 12543, 14080,
  15804
};

void setup()
{
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  val = analogRead(2); // analog input 2 is on digital pin 4
  
  // if the resistance on the analog input drops below a threshold
  // (i.e. something is connected to it)...
  if (val < 1000) {
    digitalWrite(2, HIGH);
    
    // translate the analog input value (0 to 1023) into a delay time
    // (in microseconds). first, map the input value to a frequency (in hertz).
    // then, translate the frequency into microseconds (e.g. a frequency of
    // 2093 hertz has a duration of 1 / 2093 of a second, which is equal to
    // 1,000,000 microseconds divided by 2093). divide by two because half
    // of the tone is with the pin low, half with the pin high.
    d = 1000000L / map(val, 1023, 0, 880, 15804) / 2;
    
    for (int i = 0; i < 10; i++) {
      digitalWrite(0, HIGH);
      delayMicroseconds(d);
      digitalWrite(0, LOW);
      delayMicroseconds(d);
    }
    digitalWrite(2, LOW);
  }
  
  val = analogRead(3); // analog input 3 is on digital pin 3
  
  // if the resistance on the analog input drops below a threshold
  // (i.e. something is connected to it)...
  if (val < 1000) {
    digitalWrite(2, HIGH);
    
    // same translation as above, except map the input value to an index
    // of an array of pre-defined frequencies (discrete notes).
    d = 1000000L / freqs[constrain(map(val, 1000, 0, 0, 20), 0, 20)] / 2;
   
    // play the tone for the same amount of time, even though some notes
    // are longer than others. (i.e. higher frequencies mean lower delays,
    // which means you need to play them more often).
    int n = 30000L / d / 2;
    for (int i = 0; i < n; i++) {
      digitalWrite(0, HIGH);
      delayMicroseconds(d);
      digitalWrite(0, LOW);
      delayMicroseconds(d);
    }
    digitalWrite(2, LOW);
  }
}
