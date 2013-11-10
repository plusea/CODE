void circle() {
  
  background(255);

  for (int i = 0; i < sensorValues.length; i++) {
    //println(sensorValues[i]);

    float mappedValue = map(sensorValues[i], 900, 1023, 0, 150);
    float circleSize = mappedValue;
    stroke(0);
    strokeWeight(2);
    fill(64*i, 32*i, 255);

    pushMatrix();
    rotate(i*TWO_PI/sensorValues.length); 
    ellipse(100, 0, circleSize, circleSize);
    
    fill(0,100);
    strokeWeight(5);
    
    if (mappedValue/2 < (sensorThreshold/2)) {
      fill(255);
      sound(i);
      println(i);
    }
    
    ellipse(100, 0, (sensorThreshold/2), (sensorThreshold/2));
    popMatrix();
  }
}

