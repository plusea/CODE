int accelValueXYZ;

void acelero(){
  // read raw accel/gyro measurements from device
  //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);

  int sensoVal = ReadSensor();
  accelValueXYZ = (ax + ay + az)/3;
  
  if (sensoVal>TRESHOLD){ //Hat der Sensor ausglöst?
    //input = constrain(accelValueXYZ, 16000, 30000);
    //input = map(input, -2000, 10000, 0, 50);  //32768
    input = 50;
    brightness = 0;
    graph();
    delay(500);
  }

  else if (sensoVal < TRESHOLD){ 
    input = 0;
    brightness = 2;
    draw3(framecount++);
  }

  Serial.print(sensoVal);
  Serial.print("\t");
  Serial.print(accelValueXYZ);
  Serial.print("\t");
  Serial.print(input);
  Serial.println();
  
  delay(10);

}

int ReadSensor(){
  static unsigned long lastTime = millis();  //Variable für Zeitmerker
  static int lastValue = accelValueXYZ; //Variable für letzten Messwert
  if (millis()-lastTime < INTERVAL) return false; //Zeit noch nicht abgelaufen
  int value = accelValueXYZ; //Sensor abrufen
  int differenz = lastValue-value; //Differnz bilden abs() = Betragsfunktion
  lastValue = value; //Messwert für nächstes Mal speichern
  return differenz;
} 

