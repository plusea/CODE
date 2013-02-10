
// This is how high the sensor needs to read in order
//  to trigger a touch.  You'll find this number
//  by trial and error, or you could take readings at
//  the start of the program to dynamically calculate this.
int touchedCutoffYellow = 28;
int touchedCutoffGreen = 28;
int touchedCutoffBlue = 23;
int touchedCutoffRed = 28;
char color = 'x';
int y;
int g;
int b;
int r;

void setup(){
  //Serial.begin(9600);  //USB
  Serial.begin(57600);  //BT and USB
}

void loop(){
  // If the capacitive sensor reads above a certain threshold,
  //  turn on the LED
  int yellow = readCapacitivePin(6);
  int green = readCapacitivePin(7);
  int blue = readCapacitivePin(8);
  int red = readCapacitivePin(9);

  if (yellow > touchedCutoffYellow) y = 1; 
  else y = 0;
  if (green > touchedCutoffGreen) g = 1; 
  else g = 0;
  if (blue > touchedCutoffBlue) b = 1; 
  else b = 0;
  if (red > touchedCutoffRed) r = 1; 
  else r = 0;

  Serial.print(y);
  Serial.print(";");
  Serial.print(g);
  Serial.print(";");
  Serial.print(b);
  Serial.print(";");
  Serial.print(r);
  Serial.println("");

  //  if (yellow > touchedCutoffYellow) color = 'y';
  //  if (green > touchedCutoffGreen) color = 'g';
  //  if (blue > touchedCutoffBlue) color = 'b';
  //  if (red > touchedCutoffRed) color = 'r';
  //
  //  Serial.println(color);
  //  
  //  Serial.print("RAW");
  //    Serial.print(" -- ");
  //  Serial.print(yellow);
  //  Serial.print(" -- ");
  //  Serial.print(green);
  //  Serial.print(" -- ");
  //  Serial.print(blue);
  //  Serial.print(" -- ");
  //  Serial.println(red);

}

// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//          how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
//  In order for this to work now,
// The pin should have a 1+Megaohm resistor pulling
//  it up to +5v.
uint8_t readCapacitivePin(int pinToMeasure){
  // This is how you declare a variable which
  //  will hold the PORT, PIN, and DDR registers
  //  on an AVR
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  if ((pinToMeasure >= 0) && (pinToMeasure <= 7)){
    port = &PORTD;
    ddr = &DDRD;
    bitmask = 1 << pinToMeasure;
    pin = &PIND;
  }
  if ((pinToMeasure > 7) && (pinToMeasure <= 13)){
    port = &PORTB;
    ddr = &DDRB;
    bitmask = 1 << (pinToMeasure - 8);
    pin = &PINB;
  }
  if ((pinToMeasure > 13) && (pinToMeasure <= 19)){
    port = &PORTC;
    ddr = &DDRC;
    bitmask = 1 << (pinToMeasure - 13);
    pin = &PINC;
  }
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input WITHOUT the internal pull-up on
  *ddr &= ~(bitmask);
  // Now see how long the pin to get pulled up
  int cycles = 16000;
  for(int i = 0; i < cycles; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}






