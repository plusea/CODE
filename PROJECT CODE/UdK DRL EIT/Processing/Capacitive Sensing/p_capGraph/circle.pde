void circle() {
  int circleSize = 50;
  ellipseMode(RADIUS);
  background(255);
  translate(width/2, height/2);

  for (int i = 0; i < sensorValues.length; i++) {
    println(sensorValues[i]);

    pushMatrix();
    rotate(i*TWO_PI/9);
    if (sensorValues[i] > 1) fill(200, 0, 0);
    else fill(0);
    ellipse(160, 0, circleSize, circleSize);
    popMatrix();
  }
}

