// UdK - DRL - EIT
// code for 6-segment resistive sensing ball
// reads 6 analo ginput pins
// does smoothing on input by averaging over time
// prints sensor values to serial port


int onPin = 13;

void setup()
{
  pinMode(A0, INPUT_PULLUP); 
  pinMode(10, INPUT_PULLUP); 
  pinMode(11, INPUT_PULLUP); 
  digitalWrite(onPin, HIGH);

  Serial.begin(9600);  //USB
  Serial.println("starting...");
}



void loop() {
  int A1value = analogRead(A0);
  int D11value = digitalRead(11);
  int D10value = digitalRead(10);
  Serial.print(A1value);
  Serial.print(',');
  Serial.print(D11value);
  Serial.print(',');
  Serial.print(D10value);
  Serial.println();
  delay(10);

}



















