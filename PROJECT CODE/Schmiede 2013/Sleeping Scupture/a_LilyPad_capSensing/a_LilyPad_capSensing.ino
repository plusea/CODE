// capacitive sensing on lilypad simple

// readCapacitivePin
// Input: Arduino pin number
// Output: A number, from 0 to 17 expressing
// how much capacitance is on the pin
// When you touch the pin, or whatever you have
// attached to it, the number will get higher
// See more at: http://lilypadarduino.org/?p=1798#sthash.JoCMRY7h.dpuf



void setup()
{ 
Serial.begin(9600);
}



void loop() // run over and over
{
  Serial.print(readCapacitivePin(10));
} 





