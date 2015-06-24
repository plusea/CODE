int pin = 5;
volatile int state = LOW;

void setup()
{
  pinMode(pin, OUTPUT);
  attachInterrupt(0/* 
Simple Interrupt example
by: Jordan McConnell
SparkFun Electronics
created on 10/29/11
license: Beerware- feel free to use this code and maintain
attribution. If we ever meet and you are overcome with gratitude,
feel free to express your feelings via beverage.
*/

int ledPin = 13;  // LED is attached to digital pin 13
int x = 0;  // variable to be updated by the interrupt

void setup() {                
  //enable interrupt 0 (pin 2) which is connected to a button
  //jump to the increment function on falling edge
  attachInterrupt(0, increment, FALLING);
  Serial.begin(9600);  //turn on serial communication
}

void loop() {
  digitalWrite(ledPin, LOW);
  delay(3000); //pretend to be doing something useful
  Serial.println(x, DEC); //print x to serial monitor
}

// Interrupt service routine for interrupt 0
void increment() {
    x++;
    digitalWrite(ledPin, HIGH);
}
, blink, CHANGE);
}

void loop()
{
  digitalWrite(pin, state);
}

void blink()
{
  state = !state;
}
