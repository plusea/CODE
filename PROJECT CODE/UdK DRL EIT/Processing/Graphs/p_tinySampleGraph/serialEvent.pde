void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');   // get the ASCII string
  if (inString != null) {
    inString = trim(inString);
    int incomingValues[] = int(split(inString, ","));
    for (int i=0; i<maxNumberOfSensors; i++) {
      globalValues[i] = incomingValues[i];
    }
  }
}

