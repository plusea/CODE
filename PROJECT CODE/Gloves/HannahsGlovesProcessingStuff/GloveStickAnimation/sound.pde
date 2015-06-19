void sound() 
{
  if (LeftRoll_value < 10) kick2.trigger();
  if (RightRoll_value < 10) kick.trigger();
  if (LeftIndexFlex_value > 90)snare.trigger();
  if (RightIndexFlex_value > 90)hihat.trigger();
  //bass.trigger();
  //cymbal.trigger();
}

