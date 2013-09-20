void sound() 
{
  if (sensorValues[0] > 0) kick.trigger();
  if (sensorValues[1] > 0) snare.trigger();
  if (sensorValues[2] > 0) bass.trigger();
  if (sensorValues[3] > 0) cymbal.trigger();
}
