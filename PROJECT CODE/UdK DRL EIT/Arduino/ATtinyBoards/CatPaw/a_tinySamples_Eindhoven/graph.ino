void graph(){
    //mySerial.println("Loop G");
    int sensorValue1 = analogRead(1);
    int sensorValue2 = analogRead(2);
    int sensorValue3 = analogRead(3);
    mySerial.print(sensorValue1);
    mySerial.print(",");
    mySerial.print(sensorValue2);
    mySerial.print(",");
    mySerial.print(sensorValue3);
    mySerial.println();
  }

