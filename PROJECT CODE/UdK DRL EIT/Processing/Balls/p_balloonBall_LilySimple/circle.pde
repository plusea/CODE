void circle() {

  background(255);
  fill(0);
  text("BALLOON BALL DEMO", 50, 50);
  text("press 'g' for graph", 50, 150);
  text("press 'v' for visualization", 50, 200);
  
  ellipseMode(RADIUS);
  translate(width/2, height/2);

  for (int i = 0; i < sensorValues.length; i++) {
    if (sensorValues[i] > 1) {
      fill(255, 100, 100);
      sound(i);
    }
    else {
      fill(0);
    }
    float circleSize = 100;
    strokeWeight(0);

    pushMatrix();
    rotate(i*TWO_PI/sensorValues.length); 
    ellipse(300, 0, circleSize, circleSize);
    popMatrix();
  }
}

