void sound() 
{
  if (sensorValues[0] > 1) kick.trigger();
  if (sensorValues[1] > 1) snare.trigger();
  if (sensorValues[2] > 1) bass.trigger();
  if (sensorValues[3] > 1) cymbal.trigger();
  if (sensorValues[4] > 1) hihat.trigger();
  if (sensorValues[5] > 1) kick2.trigger();
  if (sensorValues[6] > 1) loosekick.trigger();
  if (sensorValues[7] > 1) loosekick2.trigger();
  //if (sensorValues[8] > 1) sample.trigger();
}
