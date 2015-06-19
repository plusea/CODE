
void oscEvent(OscMessage theOscMessage)
{
  String addrPattern = theOscMessage.addrPattern();
  // Print address pattern to terminal
  //println(addrPattern);
  
  // LEFT FINGERPOINT TRIGGER
  if (addrPattern.equals("/LeftFP")) {
    LeftFP_value = theOscMessage.get(0).floatValue();
  }
  
  // LEFT FINGERPOINT YAW
  if (addrPattern.equals("/LeftFPyaw")) {
    LeftFPyaw_value = theOscMessage.get(0).floatValue();
  }
  
  println("LeftFP: " + LeftFP_value);
  println("LeftFPyaw: " + LeftFPyaw_value);
}

