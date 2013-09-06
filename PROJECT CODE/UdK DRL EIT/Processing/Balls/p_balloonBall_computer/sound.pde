void sound(int soundSample) 
{
  switch(soundSample) {
  case 0: 
    kick2.trigger();
    break;
  case 1: 
    kick.trigger();
    break;
  case 2: 
    snare.trigger();
    break;
  case 3: 
    bass.trigger();
    break;
  case 4: 
    cymbal.trigger();
    break;
  case 5: 
    hihat.trigger();
    break;
  }
}

