// capacitive sensing on lilypad simple

// readCapacitivePin
// Input: Arduino pin number
// Output: A number, from 0 to 17 expressing
// how much capacitance is on the pin
// When you touch the pin, or whatever you have
// attached to it, the number will get higher
// See more at: http://lilypadarduino.org/?p=1798#sthash.JoCMRY7h.dpuf

int capPin[9] = {5,6,9,10,11,16,17,18,19};
int capValue[9];


void setup()
{ 
Serial.begin(9600);
}



void loop() // run over and over
{
  for(int i = 0; i<9; i++){
  capValue[i] = readCapacitivePin(capPin[i]);
  Serial.print(capValue[i]);
  if(i<9-1) Serial.print(",");
  }
  Serial.println();
} 





