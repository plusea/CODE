
void oscEvent(OscMessage theOscMessage)
{
  String addrPattern = theOscMessage.addrPattern();
  // Print address pattern to terminal
  //println(addrPattern);
  
  
  // LEFT BUTTON PRESS
  if (addrPattern.equals("/LeftButtonPress")) {
    LeftButtonPress_value = theOscMessage.get(0).floatValue();
  }
  // LEFT ROLL
  if (addrPattern.equals("/LeftRoll")) {
    LeftRoll_value = theOscMessage.get(0).floatValue();
  }
  // LEFT PITCH
  if (addrPattern.equals("/LeftPitch")) {
    LeftPitch_value = theOscMessage.get(0).floatValue();
  }
  // LEFT INDEX FLEX
  if (addrPattern.equals("/LeftIndexFlex")) {
    LeftIndexFlex_value = theOscMessage.get(0).floatValue();
  }
  // LEFT MIDDLE FLEX
  if (addrPattern.equals("/LeftMiddleFlex")) {
    LeftMiddleFlex_value = theOscMessage.get(0).floatValue();
  }
  // LEFT RING FLEX
  if (addrPattern.equals("/LeftRingFlex")) {
    LeftRingFlex_value = theOscMessage.get(0).floatValue();
  }
  
    // RIGHT ROLL
  if (addrPattern.equals("/RightRoll")) {
    RightRoll_value = theOscMessage.get(0).floatValue();
  }
  // RIGHT PITCH
  if (addrPattern.equals("/RightPitch")) {
    RightPitch_value = theOscMessage.get(0).floatValue();
  }
  // RIGHT FLEX
  if (addrPattern.equals("/RightIndexFlex")) {
    RightIndexFlex_value = theOscMessage.get(0).floatValue();
  }
  // RIGHT MIDDLE FLEX
  if (addrPattern.equals("/RightMiddleFlex")) {
    RightMiddleFlex_value = theOscMessage.get(0).floatValue();
  }
  // RIGHT RING FLEX
  if (addrPattern.equals("/RightRingFlex")) {
    RightRingFlex_value = theOscMessage.get(0).floatValue();
  }
  
  println("LeftRoll: " + LeftRoll_value);
  println("LeftIndexFlex: " + LeftIndexFlex_value);
  println("LeftButonPress: " + LeftButtonPress_value);
}

