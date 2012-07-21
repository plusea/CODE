#include <avr/pgmspace.h>  //This is in the Arduino library

int pins[4];
int blinkdelay = 200;   //This basically controls brightness. Lower is dimmer
int runspeed = 150;      //smaller = faster

const int ledPins[12][2] ={ // This stores the led pins order NOTE:You may need to change the order of these
  {
    3,0  } 
  , 
  {
    3,2  }
  ,
  {
    3,1  }
  ,
  {
    2,0  }
  ,
  {
    2,3  }
  ,
  {
    2,1  }
  ,
  {
    1,0  }
  ,
  {
    1,2  }
  ,
  {
    1,3  }
  , 
  {
    0,3  }
  ,
  {
    0,2  }
  ,
  {
    0,1  }
  ,


};

byte displays[][12] PROGMEM ={  // This stores the array in Flash ROM. You can easily have 500+ frames.
  //left right blinking
   {0,1,1,1,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,1,1,1,0},
   // out in blinking
   {0,0,0,0,0,1,1,0,0,0,0,0},
   {1,1,0,0,0,0,0,0,0,0,1,1},
   // counting in binary
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,1},
   {0,0,0,0,0,0,0,0,0,0,1,0},
   {0,0,0,0,0,0,0,0,0,0,1,1},
   {0,0,0,0,0,0,0,0,0,1,0,0},
   {0,0,0,0,0,0,0,0,0,1,0,1},
   {0,0,0,0,0,0,0,0,0,1,1,0},
   {0,0,0,0,0,0,0,0,0,1,1,1},
   {0,0,0,0,0,0,0,0,1,0,0,0},
   {0,0,0,0,0,0,0,0,1,0,1,0}
};


// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digital pin as an output:
  pins[0] = 2;
  pins[1] = 3;
  pins[2] = 4;
  pins[3] = 5;
  sequenceon(); // Does one loop of the cylon effect
}

// the loop() method runs over and over again,
// as long as the Arduino has power

void loop()                     
{
    sequenceon(); //Turns on cylon effect
//  displayChar(0,1, 100); //In/out blinking
//  displayChar(4,14, 200); //Counts to 15 in binary
}

void displayChar(int from, int through, int tranSpeed)// loads a Pattern from above. From & though spesify what patterns to show. tranSpeed is the speed of the frames
{
  boolean run = true;
  byte k;
  int t = from;
  while(run == true)
  {
    for(int i = 0; i < tranSpeed; i++)
    {
      for(int j = 0; j < 12; j++)
      {
        k = pgm_read_byte(&(displays[t][j]));
        if (k == 2)
        {
          run = false;
        }
        else if(k == 1)
        {
          turnon(j);
          delayMicroseconds(blinkdelay);
          alloff();
        }
        else if(k == 0)
        {
          delayMicroseconds(blinkdelay);
        }
      }
    }
    if(through == t){
      return;
    }
    t++;
  }
}
void ledSpecify(int highPin, int lowPin) // This allows you to manually control which pin goes low & which one goes high
{
  for(int i; i < 4; i++){
    pinMode(pins[i], INPUT);
  }
  pinMode(pins[highPin], OUTPUT); 
  digitalWrite(pins[highPin], HIGH);
  pinMode(pins[lowPin], OUTPUT); 
  digitalWrite(pins[lowPin], LOW); 
}

void turnon(int led) // This turns on a certian led from the list of leds
{
  int pospin = ledPins[led][0] + 2;
  int negpin = ledPins[led][1] + 2;
  pinMode (pospin, OUTPUT);
  digitalWrite (pospin, HIGH);
  pinMode (negpin, OUTPUT);
  digitalWrite (negpin, LOW);
}


void alloff() // This turns all the LED's off
{
  for(int i = 0; i < 5; i++)
  {
    pinMode (pins[i], INPUT);
  }
}

void sequenceon() // This handles the cylon effect
{
  for(int i = 0; i < 12; i++)
  {
    turnon(i);
    delay(100);   
    alloff(); 
  }
  for(int n = 10; n > 0; n--)
  {
    turnon(n);
    delay(100);   
    alloff();   
  }
}




