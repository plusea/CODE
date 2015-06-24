/* 
Simple Interrupt example 2
by: Jordan McConnell
SparkFun Electronics
created on 10/29/11
license: Beerware- feel free to use this code and maintain
attribution. If we ever meet and you are overcome with gratitude,
feel free to express your feelings via beverage.
*/

int ledPin = 13; // LED is attached to digital pin 13
int x = 0; // variable to be updated by the interrupt

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void setup() {                
  //enable interrupt 0 which uses pin 2
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
  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > 250)
  {
    x++;
    digitalWrite(ledPin, HIGH);
    last_button_time = button_time;
  }
}
