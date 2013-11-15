void animateCircle(){
  sensorValue = analogRead(A1);  // read sensor value
  Serial.print(sensorValue);  // print sensor value to serial port for debugging
  Serial.print("\t");  // print sensor value to serial port for debugging
  sensorValue = constrain(sensorValue, 50, 1000);  // map sensor value to number of LEDs
  sensorValue = map(sensorValue, 50, 1000, 0, 6);  // map sensor value to a chosen number of different colours
  Serial.println(sensorValue);  // print sensor value to serial port for debugging

  if(sensorValue != 5) colorValue = sensorValue;
  if(colorValue == 0) { myColor = colorON; circleSpeed = 10; }
  if(colorValue == 1) {  myColor = colorRed; circleSpeed = 20; }
  if(colorValue == 2) { myColor = colorPurple; circleSpeed = 30; }
  if(colorValue == 3) { myColor = colorTurquoise; circleSpeed = 40; }
  if(colorValue == 4) { myColor = colorYellow; circleSpeed = 50; }




  for(int h=3; h<=20; h++){ 

    for(int i=3; i<=20; i++) allOFF();

    //    struct color randomColor = { 
    //    random(1,255), random(1,255), random(1,255)
    //    };
    pixels[0] = myColor;
    pixels[1] = myColor;
    pixels[h-1] = myColor;
    pixels[h] = myColor;
    pixels[h+1] = myColor;

    show((byte *)pixels, sizeof(pixels));  // update pixels
    delay(circleSpeed);

  }


}










