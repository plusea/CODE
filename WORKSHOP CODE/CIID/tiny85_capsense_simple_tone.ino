// capacitive sensing example
// circuit: led on pin 0, 10M resistor between pins 1 and 2, electrode on pin 2
// the higher the capacitance on the electrode, the faster the led will blink

#include <CapacitiveSensor.h>

CapacitiveSensor  cs = CapacitiveSensor(1,2);        // 10M resistor between pins 1 & 2, pin 2 is sensor pin, add a wire and or foil if desired

long min_v = 0, max_v = 0;

long d, d2;


void setup()                    
{
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
  pinMode(0, OUTPUT);
}

void loop()                    
{
  long val =  cs.capacitiveSensor(10);
  
  // map capacitive value to blink speed
  d = constrain(map(val, 0, 100, 500, 10), 10, 500);
  
  digitalWrite(0, HIGH);
  delay(d);
  digitalWrite(0, LOW);
  delay(d);
}

