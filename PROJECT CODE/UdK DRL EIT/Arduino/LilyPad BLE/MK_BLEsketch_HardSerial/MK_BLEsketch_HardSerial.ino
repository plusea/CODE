long interval = 1000; 

void setup()
{
  Serial.begin(19200);
  pinMode(13, OUTPUT);
}

void loop() // run over and over
{

    delay(interval);          // wait for 1 sec
    digitalWrite(13, HIGH);   // set the LED on

    Serial.write(0x4D);
    Serial.write(0x2A);
    Serial.write(0x10);
    Serial.write(0x20);

    delay(interval);         // wait for 1 sec
    digitalWrite(13, LOW);   // set the LED off
}
