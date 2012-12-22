class Graph {
  int smoothAmount = 10;
  float graphX = 0;
  float speed=1;

  float previousValue;
  float previousGraphY;

  boolean hump=false;
  boolean peak1 = true;
  boolean peak2 = false;

  float[] readings = new float [smoothAmount];  // the readings from the analog input
  int index = 0;  // the index of the current reading
  float total = 0;  // the running total
  float average = 0;  // the average
  float steigung;
  float oldAverage;
  float oldSteigung;
  int peak1value;
  int peak2value;
  int result;
  int biggerValue;
  color graphColor;
  boolean smoothingSetting;

  Graph (color colorValue, boolean smoothing){
    graphColor = colorValue;
    smoothingSetting = smoothing;

  }

  void peak(int incomingValue) {
    int graphValue = incomingValue;

    if(smoothing) {
      total = total - readings[index];  // subtract the last reading
      readings[index] = graphValue;  // read from the sensor
      total= total + readings[index];  // add the reading to the total
      index = index + 1;  // advance to the next position in the array
      if (index >= smoothAmount) index = 0;  // if we're at the end of the array, wrap around to the beginning

      oldAverage = average;
      oldSteigung = steigung;

      average = total / smoothAmount;  // calculate the average
      steigung = average - oldAverage;  // calculate the inclination
    }

    else average = graphValue;
    hump = false;

    if (average > 0){
      if (oldSteigung*steigung < 0 && average-oldAverage < 0.3) {
        println(average-oldAverage);
        hump = true;
      }
    }


    float graphY = map(graphValue, 0, 1023, 0, height);

    strokeWeight(2);
    stroke(graphColor);
    fill(graphColor);
    line(graphX, height - previousGraphY, graphX+1, height - graphY);

    if(hump) {
      ellipse(graphX+1, height - graphY, 10,10);
      textFont(myFont);
      text(graphValue, graphX+1, height - graphY);
    }

    previousGraphY = graphY;

    if (graphX >= width) {  // if you've drawn to the edge of the window, start at the beginning again
      if(graphColor == rightColor) saveFrame();
      graphX = 0;
      background(255);
      grid();
        println("EEEEEEEEEEEEEEEEEEEEEEEEE");
    }
    else graphX+=speed;
  }

}









