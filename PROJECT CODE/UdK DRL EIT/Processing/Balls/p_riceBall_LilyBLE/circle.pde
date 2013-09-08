void circle() {
  
  background(255);
  text("RICE BALL DEMO", 50, 50);
  text("press 'g' for graph", 50, 150);
  text("press 'v' for visualization", 50, 200);
  text("press 'arrow up' to increase threshold", 50, 250);
  text("press 'arrow down' to decrease threshold", 50, 300);
  ellipseMode(RADIUS);
  translate(width/2, height/2);

  for (int i = 0; i < sensorValues.length; i++) {
    //println(sensorValues[i]);

    float mappedValue = map(sensorValues[i], 0, 500, 0, 255);
    float circleSize = mappedValue/2;
    stroke(0);
    strokeWeight(2);
    fill(64*i, 32*i, 255);

    pushMatrix();
    rotate(i*TWO_PI/sensorValues.length); 
    ellipse(300, 0, circleSize, circleSize);
    
    fill(0,100);
    strokeWeight(5);
    
    if (mappedValue/2 < (sensorThreshold/2)) {
      fill(255);
      sound(i);
      println(i);
    }
    
    ellipse(300, 0, (sensorThreshold/2), (sensorThreshold/2));
    popMatrix();
  }
}

