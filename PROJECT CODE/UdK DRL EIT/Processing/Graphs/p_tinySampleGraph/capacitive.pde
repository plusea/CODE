void capacitive() {
  if (globalValues.length <= maxNumberOfSensors && globalValues.length > 0) {
    for (int i = 0; i < globalValues.length; i++) {

      if (globalValues[0] == 0) fill(0);
      if (globalValues[0] == 4) fill(200, 0, 0);
      rect(width/4, height/2, 100, 100);
      if (globalValues[1] == 0) fill(0);
      if (globalValues[1] == 3) fill(200, 0, 0);
      rect(3*width/4, height/2, 100, 100);
    }
  }
}

