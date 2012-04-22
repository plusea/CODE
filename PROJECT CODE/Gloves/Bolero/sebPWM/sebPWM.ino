
#define LED0pin 2 
#define LED1pin 3
#define LED2pin 4
#define LED3pin 5
#define LED4pin 6
#define LED5pin 7
#define LED6pin 8
#define LED7pin 9
#define LED8pin 10
#define LED9pin 11
#define LED10pin 12
#define LED11pin 13
#define LED12pin 14
#define LED13pin 15
#define LED14pin 16
#define LED15pin 17

#define AUX4 19
#define AUX5 18
#define AUX6 0 // = A4
#define AUX7 1 // = A5

unsigned char counter = 0;

unsigned short activeLEDcounter = 0;

unsigned char LEDdutyCycle[16];
unsigned char LEDactivityCountdown[16];

unsigned char DCcount = 0;
char numActiveLEDs = 0;

boolean LEDactive[16] = {
  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
boolean LEDdirection[16] = {
  true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true};
  
unsigned char randomNumers[256] =
{
3, 5, 9, 11, 7, 4, 15, 2, 8, 1, 10, 12, 13, 14, 6,
12, 8, 1, 10, 4, 2, 9, 6, 13, 14, 5, 15, 3, 11, 7,
1, 10, 14, 9, 7, 3, 8, 2, 5, 13, 12, 4, 15, 11, 6,
11, 5, 7, 8, 6, 9, 2, 4, 10, 15, 14, 3, 1, 12, 13,
14, 9, 4, 10, 15, 7, 1, 3, 6, 8, 13, 5, 2, 11, 12,
3, 4, 5, 15, 13, 11, 1, 9, 10, 8, 6, 14, 7, 12, 2,
4, 10, 1, 8, 9, 7, 11, 12, 2, 15, 6, 3, 14, 13, 5,
15, 10, 13, 11, 4, 1, 12, 3, 7, 9, 8, 2, 14, 6, 5,
12, 2, 8, 1, 3, 13, 5, 14, 7, 4, 11, 15, 9, 6, 10,
13, 10, 5, 4, 1, 11, 6, 7, 8, 9, 2, 3, 15, 12, 14,
15, 8, 3, 13, 12, 4, 1, 9, 7, 6, 2, 10, 11, 5, 14,
4, 10, 8, 5, 6, 12, 11, 7, 14, 9, 13, 3, 1, 15, 2,
5, 15, 4, 2, 8, 7, 14, 10, 11, 3, 6, 13, 12, 1, 9,
3, 12, 10, 13, 15, 5, 1, 9, 4, 8, 14, 11, 7, 2, 6,
13, 14, 4, 15, 11, 10, 6, 8, 5, 3, 9, 2, 1, 12, 7,
12, 4, 15, 14, 10, 1, 5, 7, 11, 6, 9, 8, 3, 2, 13
};


unsigned char randArrayIndx = 0;

#define getRand() (randomNumers[randArrayIndx++])


void setup()
{
//  Serial.begin(9600); // will interfere with xIMU comunication!!!
  pinMode(LED0pin, OUTPUT);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);
  pinMode(LED4pin, OUTPUT);
  pinMode(LED5pin, OUTPUT);
  pinMode(LED6pin, OUTPUT);
  pinMode(LED7pin, OUTPUT);
  pinMode(LED8pin, OUTPUT);
  pinMode(LED9pin, OUTPUT);
  pinMode(LED10pin, OUTPUT);
  pinMode(LED11pin, OUTPUT);
  pinMode(LED12pin, OUTPUT);
  pinMode(LED13pin, OUTPUT);
  pinMode(LED14pin, OUTPUT);
  pinMode(LED15pin, OUTPUT);

  // set x-IMU pins as inputs and set pull-up resistors
  pinMode(AUX4, INPUT);
  digitalWrite(AUX4, HIGH); // internal pullup for triggerpin
  pinMode(AUX5, INPUT);
  digitalWrite(AUX5, HIGH); // internal pullup for triggerpin
  pinMode(AUX6, INPUT);
  digitalWrite(AUX6, HIGH); // internal pullup for triggerpin
  pinMode(AUX7, INPUT);
  digitalWrite(AUX7, HIGH); // internal pullup for triggerpin
}

void loop() 
{

  //if(counter & (0b00000001 << 8)) 
  
//   getMode();
//   
//   return;
  
  if (DCcount % 16 == 0)
  {
    updateBrightness();

    updateLEDactivityCountdown();

    if(activeLEDcounter++ == 511)
    {
      int mode = getMode();
      numActiveLEDs = mode;
      activeLEDcounter = 0;
      updateActiveLEDs();
      
     
    }
  }
  updateDutyCycle();
  counter++;
}

unsigned char getMode() 
{
  char lMode = 0;
  unsigned char value1 = digitalRead(AUX4);
  unsigned char value2 = digitalRead(AUX5);
  unsigned char value3 = digitalRead(AUX6);
  unsigned char value4 = digitalRead(AUX7);
  if(value1==1) lMode |= 0x01;
  if(value2==1) lMode |= 0x01 << 1;
  if(value3==1) lMode |= 0x01 << 2;
  if(value4==1) lMode |= 0x01 << 3;
  
  
//  
//  value1 == 1 ? digitalWrite(6, HIGH) : digitalWrite(6, LOW); 
//  value2 == 1 ? digitalWrite(7, HIGH) : digitalWrite(7, LOW);  // AX7 
//  value3 == 1 ? digitalWrite(4, HIGH) : digitalWrite(4, LOW);  // AX6
//  value4 == 1 ? digitalWrite(5, HIGH) : digitalWrite(5, LOW);  // AX4
  
  return lMode;
}

void updateLEDactivityCountdown()
{
  for(int i = 0; i < 16; i++)
  {
    if(LEDactivityCountdown[i] != 0)
      LEDactivityCountdown[i]--;

    if(LEDactivityCountdown[i] == 1)
      LEDactive[i] = true;

  }
}

void updateActiveLEDs() 
{    // call this every 512 'updateBrightness' calls

    for (int i = 0; i < 16; i++)
    LEDactive[i] = false;

  for (int i = 0; i < numActiveLEDs; i++) 
  {
    char num;
    do {
      num = getRand();
    } 
    while(LEDactive[num] == true);
    LEDactive[num] = true;
    //LEDactivityCountdown[i] = random(0, 256);
  }
}

void updateBrightness ()
{        // call this with a frequency proportional to storm speed

for(int i=0; i<16;i++)
{
 if(LEDactive[i] && LEDdirection[i])
  {                              
    LEDdutyCycle[i]++;             
    if(LEDdutyCycle[i] == 255)     
      LEDdirection[i] = false;     
  }                              
  else if(LEDdutyCycle[i] != 0)    
  {                              
    LEDdutyCycle[i]--;             
    if(LEDdutyCycle[i] == 0)       
    {                            
      if(LEDactive[i])             
       LEDdirection[i] = true;          
    }                            
  }  
}  
//  // update LED1 brightness
//  if(LEDactive[0] && LEDdirection[0])
//  {                              
//    LEDdutyCycle[0]++;             
//    if(LEDdutyCycle[0] == 255)     
//      LEDdirection[0] = false;     
//  }                              
//  else if(LEDdutyCycle[0] != 0)    
//  {                              
//    LEDdutyCycle[0]--;             
//    if(LEDdutyCycle[0] == 0)       
//    {                            
//      if(LEDactive[0])             
//       LEDdirection[0] = true;          
//    }                            
//  }       
//
//  if(LEDactive[1] && LEDdirection[1])
//  {                              
//    LEDdutyCycle[1]++;             
//    if(LEDdutyCycle[1] == 255)     
//      LEDdirection[1] = false;     
//  }                              
//  else if(LEDdutyCycle[1] != 0)    
//  {                              
//    LEDdutyCycle[1]--;             
//    if(LEDdutyCycle[1] == 0)       
//    {                            
//      if(LEDactive[1])             
//       LEDdirection[1] = true;          
//    }                            
//  }                                
//  
//    if(LEDactive[2] && LEDdirection[2])
//  {                              
//    LEDdutyCycle[2]++;             
//    if(LEDdutyCycle[2] == 255)     
//      LEDdirection[2] = false;     
//  }                              
//  else if(LEDdutyCycle[2] != 0)    
//  {                              
//    LEDdutyCycle[2]--;             
//    if(LEDdutyCycle[2] == 0)       
//    {                            
//      if(LEDactive[2])             
//       LEDdirection[2] = true;          
//    }                            
//  }                              
//
//  if(LEDactive[3] && LEDdirection[3])
//  {                              
//    LEDdutyCycle[3]++;             
//    if(LEDdutyCycle[3] == 255)     
//      LEDdirection[3] = false;     
//  }                              
//  else if(LEDdutyCycle[3] != 0)    
//  {                              
//    LEDdutyCycle[3]--;             
//    if(LEDdutyCycle[3] == 0)       
//    {                            
//      if(LEDactive[3])             
//       LEDdirection[3] = true;          
//    }                            
//  }                              
//  
//    if(LEDactive[4] && LEDdirection[4])
//  {                              
//    LEDdutyCycle[4]++;             
//    if(LEDdutyCycle[4] == 255)     
//      LEDdirection[4] = false;     
//  }                              
//  else if(LEDdutyCycle[4] != 0)    
//  {                              
//    LEDdutyCycle[4]--;             
//    if(LEDdutyCycle[4] == 0)       
//    {                            
//      if(LEDactive[4])             
//       LEDdirection[4] = true;          
//    }                            
//  }                   
//
//  if(LEDactive[5] && LEDdirection[5])
//  {                              
//    LEDdutyCycle[5]++;             
//    if(LEDdutyCycle[5] == 255)     
//      LEDdirection[5] = false;     
//  }                              
//  else if(LEDdutyCycle[5] != 0)    
//  {                              
//    LEDdutyCycle[5]--;             
//    if(LEDdutyCycle[5] == 0)       
//    {                            
//      if(LEDactive[5])             
//       LEDdirection[5] = true;          
//    }                            
//  }                       
//
//  if(LEDactive[6] && LEDdirection[6])
//  {                              
//    LEDdutyCycle[6]++;             
//    if(LEDdutyCycle[6] == 255)     
//      LEDdirection[6] = false;     
//  }                              
//  else if(LEDdutyCycle[6] != 0)    
//  {                              
//    LEDdutyCycle[6]--;             
//    if(LEDdutyCycle[6] == 0)       
//    {                            
//      if(LEDactive[6])             
//       LEDdirection[6] = true;          
//    }                            
//  }                                
//
//  if(LEDactive[7] && LEDdirection[7])
//  {                              
//    LEDdutyCycle[7]++;             
//    if(LEDdutyCycle[7] == 255)     
//      LEDdirection[7] = false;     
//  }                              
//  else if(LEDdutyCycle[7] != 0)    
//  {                              
//    LEDdutyCycle[7]--;             
//    if(LEDdutyCycle[7] == 0)       
//    {                            
//      if(LEDactive[7])             
//       LEDdirection[7] = true;          
//    }                            
//  }               
//
//  if(LEDactive[8] && LEDdirection[8])
//  {                              
//    LEDdutyCycle[8]++;             
//    if(LEDdutyCycle[8] == 255)     
//      LEDdirection[8] = false;     
//  }                              
//  else if(LEDdutyCycle[8] != 0)    
//  {                              
//    LEDdutyCycle[8]--;             
//    if(LEDdutyCycle[8] == 0)       
//    {                            
//      if(LEDactive[8])             
//       LEDdirection[8] = true;          
//    }                            
//  }                                
//  
//    if(LEDactive[9] && LEDdirection[9])
//  {                              
//    LEDdutyCycle[9]++;             
//    if(LEDdutyCycle[9] == 255)     
//      LEDdirection[9] = false;     
//  }                              
//  else if(LEDdutyCycle[9] != 0)    
//  {                              
//    LEDdutyCycle[9]--;             
//    if(LEDdutyCycle[9] == 0)       
//    {                            
//      if(LEDactive[9])             
//       LEDdirection[9] = true;          
//    }                            
//  }                          
//
//  if(LEDactive[10] && LEDdirection[10])
//  {                              
//    LEDdutyCycle[10]++;             
//    if(LEDdutyCycle[10] == 255)     
//      LEDdirection[10] = false;     
//  }                              
//  else if(LEDdutyCycle[10] != 0)    
//  {                              
//    LEDdutyCycle[10]--;             
//    if(LEDdutyCycle[10] == 0)       
//    {                            
//      if(LEDactive[10])             
//       LEDdirection[10] = true;          
//    }                            
//  }                  
//
//  if(LEDactive[11] && LEDdirection[11])
//  {                              
//    LEDdutyCycle[11]++;             
//    if(LEDdutyCycle[11] == 255)     
//      LEDdirection[11] = false;     
//  }                              
//  else if(LEDdutyCycle[11] != 0)    
//  {                              
//    LEDdutyCycle[11]--;             
//    if(LEDdutyCycle[11] == 0)       
//    {                            
//      if(LEDactive[11])             
//       LEDdirection[11] = true;          
//    }                            
//  }                        
//
//  if(LEDactive[12] && LEDdirection[12])
//  {                              
//    LEDdutyCycle[12]++;             
//    if(LEDdutyCycle[12] == 255)     
//      LEDdirection[12] = false;     
//  }                              
//  else if(LEDdutyCycle[12] != 0)    
//  {                              
//    LEDdutyCycle[12]--;             
//    if(LEDdutyCycle[12] == 0)       
//    {                            
//      if(LEDactive[12])             
//       LEDdirection[12] = true;          
//    }                            
//  }                  
//
//  if(LEDactive[13] && LEDdirection[13])
//  {                              
//    LEDdutyCycle[13]++;             
//    if(LEDdutyCycle[13] == 255)     
//      LEDdirection[13] = false;     
//  }                              
//  else if(LEDdutyCycle[13] != 0)    
//  {                              
//    LEDdutyCycle[13]--;             
//    if(LEDdutyCycle[13] == 0)       
//    {                            
//      if(LEDactive[13])             
//       LEDdirection[13] = true;          
//    }                            
//  }                                
//  
//  if(LEDactive[14] && LEDdirection[14])
//  {                              
//    LEDdutyCycle[14]++;             
//    if(LEDdutyCycle[14] == 255)     
//      LEDdirection[14] = false;     
//  }                              
//  else if(LEDdutyCycle[14] != 0)    
//  {                              
//    LEDdutyCycle[14]--;             
//    if(LEDdutyCycle[14] == 0)       
//    {                            
//      if(LEDactive[14])             
//       LEDdirection[14] = true;          
//    }                            
//  }                              
//  
//  if(LEDactive[15] && LEDdirection[15])
//  {                              
//    LEDdutyCycle[15]++;             
//    if(LEDdutyCycle[15] == 255)     
//      LEDdirection[15] = false;     
//  }                              
//  else if(LEDdutyCycle[15] != 0)    
//  {                              
//    LEDdutyCycle[15]--;             
//    if(LEDdutyCycle[15] == 0)       
//    {                            
//      if(LEDactive[15])             
//       LEDdirection[15] = true;          
//    }                            
//  }                              
//  // update LED2 brightness
//  if(LEDactive[[1] && (LEDdutyCycle[[1] != 255)) LEDdutyCycle[[1]++;
//  else if(LEDdutyCycle[[1] != 0) LEDdutyCycle[[1]--;
//
//  // update LED3 brightness
//  if(LEDactive[[2] && (LEDdutyCycle[[2] != 255)) LEDdutyCycle[[2]++;
//  else if(LEDdutyCycle[[2] != 0) LEDdutyCycle[[2]--;
}


void updateDutyCycle() 
{    // call this as frequencty as possible

    PORTD &= ~0b00000100;
  if (DCcount < LEDdutyCycle[0]) PORTD |= 0b00000100;
  PORTD &= ~0b00001000; 
  if (DCcount < LEDdutyCycle[1]) PORTD |= 0b00001000; 
  PORTD &= ~0b00010000; 
  if (DCcount < LEDdutyCycle[2]) PORTD |= 0b00010000; 
  PORTD &= ~0b00100000;
  if (DCcount < LEDdutyCycle[3]) PORTD |= 0b00100000; 
  PORTD &= ~0b01000000;
  if (DCcount < LEDdutyCycle[4]) PORTD |= 0b01000000; 
  PORTD &= ~0b10000000;
  if (DCcount < LEDdutyCycle[5]) PORTD |= 0b10000000;

  PORTB = 0;
  if (DCcount < LEDdutyCycle[6]) PORTB |= 0b00000001;
  if (DCcount < LEDdutyCycle[7]) PORTB |= 0b00000010;
  if (DCcount < LEDdutyCycle[8]) PORTB |= 0b00000100; 
  if (DCcount < LEDdutyCycle[9]) PORTB |= 0b00001000; 
  if (DCcount < LEDdutyCycle[10]) PORTB |= 0b00010000; 
  if (DCcount < LEDdutyCycle[11]) PORTB |= 0b00100000;

  PORTC = 0;
  if (DCcount < LEDdutyCycle[12]) PORTC |= 0b00000001;
  if (DCcount < LEDdutyCycle[13]) PORTC |= 0b00000010; 
  if (DCcount < LEDdutyCycle[14]) PORTC |= 0b00000100;
  if (DCcount < LEDdutyCycle[15]) PORTC |= 0b00001000;

  DCcount++;

}



///*Software PWM on arduino mini
// Ernst Christensen 16.okt. 2011
// copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
// */
//
//
//int leds[]={
//  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16
//const int numberLEDs = 16;
//
//
//int r[] = {
//  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16
//int rLength = 20;
//int RightSleeveLEDs[]={
//  2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //14
//int LeftSleeveLEDs[]={
//  4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //14
//int CollarLEDs[]={
//  2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; //16
//
//unsigned char ledValues[16];
//
//int mode;
//
//int xIMUpin1 = 19;
//int xIMUpin2 = 18;
//int xIMUpin3 = 0; // = A4
//int xIMUpin4 = 1; // = A5
//
//int value1, value2, value3, value4;
//
//int delayTime = 1; // can't be 0!
//int delayVariable = 1; // can't be 0!
//
//
//
//
//void setup(){
//  //Serial.begin(9600); // will interfere with xIMU comunication!!!
//
//  for (int z=0;z<numberLEDs;z++) pinMode(leds[z],OUTPUT);
//
//  // set x-IMU pins as inputs and set pull-up resistors
//  pinMode(xIMUpin1, INPUT);
//  digitalWrite(xIMUpin1, HIGH); // internal pullup for triggerpin
//  pinMode(xIMUpin2, INPUT);
//  digitalWrite(xIMUpin2, HIGH); // internal pullup for triggerpin
//  pinMode(xIMUpin3, INPUT);
//  digitalWrite(xIMUpin3, HIGH); // internal pullup for triggerpin
//  pinMode(xIMUpin4, INPUT);
//  digitalWrite(xIMUpin4, HIGH); // internal pullup for triggerpin
//}
//
//
//
//void loop() {
//  //mode = Serial.read();  // test
//
//  int localMode = getMode();
//  //allON();
//  if(localMode == 0)
//     allOFF();
//  else
//     ledRandomOn(localMode);
//  delay(30);
//
//  //ledPWMState(led);
//  //listenXIMU();
//  //playLEDs();
//  //allFADE();
//  //allON();
//}
//
//
//
//
//
//
//void ledRandomOn(int ledCount) 
//{
//  int randomNum = random(0, 15 -ledCount);
//  if (randomNum == 0)
//  {
//     allOFF();
//     for (int i = 0; i < ledCount; i++)
//     {
//       int ledIndex = random(0, 16);
//       digitalWrite(leds[ledIndex], HIGH); 
//     }
//  }
//}
//
//
//
//
//void ledPWMState(int ledIndex, boolean state) 
//{
//  if(state == true)
//       digitalWrite(r[ledIndex], HIGH); 
//    else
//       digitalWrite(r[ledIndex], LOW);
//}
//
//
//
//
//
//char getMode() {
//  char lMode = 0;
//  value1 = digitalRead(xIMUpin1);
//  value2 = digitalRead(xIMUpin2);
//  value3 = digitalRead(xIMUpin3);
//  value4 = digitalRead(xIMUpin4);
//  if(value1==1) lMode |= 0x01;
//  if(value2==1) lMode |= 0x01 << 1;
//  if(value3==1) lMode |= 0x01 << 2;
//  if(value4==1) lMode |= 0x01 << 3;
//  return lMode;
//}
//
//void allOFF(){
//  for(int i = 0; i<numberLEDs; i++){
//    digitalWrite(leds[i], 0);
//  }
//}
//
//
//void allON(){
//  for(int i = 0; i<numberLEDs; i++){
//    digitalWrite(leds[i], 255);
//  }
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//








