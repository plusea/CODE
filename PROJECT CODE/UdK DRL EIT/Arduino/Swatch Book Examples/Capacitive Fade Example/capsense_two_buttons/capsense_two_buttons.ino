// UdK DRL EIT
// code that plays melody

int ledPin = 0;      // select the pin for the LED
int calibration2 = 0;
int previous2;
int calibration3 = 0;
int previous3;
float fadeValue=255/2;
float fadeIncrease=0.25;


void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT); 
  // CAPACITIVE CALLIBRATION
  // calibrate pin 2:
  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration2 += chargeTime(PB2);
    delay(20);
  }
  calibration2 = (calibration2 + 4) / 8;

  // calibrate pin 3:
  delay(100);
  for (int i = 0; i < 8; i++) {
    calibration3 += chargeTime(PB3);
    delay(20);
  }
  calibration3 = (calibration3 + 4) / 8;
}



void loop() {
  analogWrite(ledPin, fadeValue);
  capSensing();
}



void capSensing(){
  // sensing on pin 3:
  int n3 = chargeTime(PB3);
  if (n3 > calibration3) fadeValue-=fadeIncrease;
  if(fadeValue < 0) fadeValue=0;
  previous3 = n3;
  delayMicroseconds(500);

  // sensing on pin 2:
  int n2 = chargeTime(PB2);
  if (n2 > calibration2) fadeValue+=fadeIncrease;
  if(fadeValue > 255) fadeValue=255;
  previous2 = n2;
  delayMicroseconds(500);
}


byte chargeTime(byte pin)
{
  byte mask = (1 << pin);
  byte i;

  DDRB &= ~mask; // input
  PORTB |= mask; // pull-up on

  for (i = 0; i < 16; i++) {
    if (PINB & mask) break;
  }

  PORTB &= ~mask; // pull-up off
  DDRB |= mask; // discharge

  return i;
}



