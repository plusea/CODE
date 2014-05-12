//                        attiny85
//                   reset -+---+- power
//  (toggled by touch) pb3 -+*  +- pb2 (analog input controls blink speed)
//      (analog input) pb4 -+   +- pb1 (analog input increases brightness)
//                  ground -+---+- pb0 (analog input decreases brightness)


// pin 4: analog input
// pin 0: fades on and off (always)
// pin 1: brightness corresponds to analog input, lower resistance -> lower voltage -> brighter LED
// pin 3: on while the analog input is active (lower voltage than calibration values)

int analoginput = 2;

// [minval, maxval) is the range of values seen during calibration
// lowestval is the lowest value seen ever
int val, prev, minval = 1023, maxval = 0, lowestval;
unsigned long lastToggleTime;
unsigned long lastBlinkTime;
int blinkState = HIGH, toggleState = HIGH;

void setup()
{
  pinMode(4, INPUT_PULLUP);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  // let analog input settle
  for (int i = 0; i < 5; i++) {
    analogRead(analoginput);
    delay(10);
  }
  
  // calibrate
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 4; j++)
      digitalWrite(j, ((i >> j) & 1) ? HIGH : LOW);
    delay(10);
    val = analogRead(analoginput);
    if (val < minval) minval = val;
    if (val > maxval) maxval = val;
  }
  
  maxval++; // ensure maxval is at least one bigger than minval
  minval = minval - (maxval - minval); // add additional buffer for noise
  val = minval;
  lowestval = minval - (maxval - minval); // assume sensor's range is at least its noise
}

void loop()
{
  //val = analogRead(analoginput);
  val = 9 * val + analogRead(analoginput);
  val /= 10;
  
  if (val < lowestval) lowestval = val;
  
  if (val < minval) analogWrite(0, constrain(map(val, lowestval, minval, 0, 255), 0, 255));
  else analogWrite(0, 255);

  if (val < minval) analogWrite(1, constrain(map(val, lowestval, minval, 255, 0), 0, 255));
  else analogWrite(1, 0);
  
  if (millis() - lastBlinkTime > constrain(map(val, lowestval, minval, 0, 1023), 0, 1023)) {
    digitalWrite(2, blinkState);
    blinkState = (blinkState == HIGH ? LOW : HIGH);
    lastBlinkTime = millis();
  }

  if (val < minval && prev >= minval) {
    if (millis() - lastToggleTime > 200) {
      digitalWrite(3, toggleState);
      toggleState = (toggleState == HIGH ? LOW : HIGH);
      lastToggleTime = millis();
    }
  }

  prev = val;
}
