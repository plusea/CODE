/*Software PWM on Attiny85
 Ernst Christensen 16.okt. 2011
 copied from here: http://arduino.cc/forum/index.php/topic,75334.0.html
 */

int led[]={
  2,1,0,3};
int count=0;
//int delayTime = 20;

int maxBrightness=100;
int arousalValue=0;
int button=0;
double dLay=20;
double lightNum=0;

void setup(){
  for (int z=0;z<5;z++){
    pinMode(led[z],OUTPUT);
  } //for z

  pinMode(4,INPUT);
  digitalWrite(4, HIGH); 
}


void loop(){
   

if (lightNum==0.0)  
   checkButton();
  
if (button==0)
  return;
  
//one light
if (button==1){  
  if (int(lightNum)==0){
    doLED(0,2,20, 60);
  }
 checkButton();
 
 //two lights
  if (int(lightNum)==1){
    doLED(1,5,20, 120);
    doLED(0,3,20, 120);
    doLED(1,4,20, 120);
    doLED(2,3,40, 120);
    doLED(0,2,40, 120);
  }
 checkButton();

 // three lights:
  if (int(lightNum)==2) {
    doLED(0,2,10, 100);
    doLED(1,3,10, 100);
    doLED(0,4,10, 200);
    doLED(0,2,10, 100);
  }
 checkButton();

  if (int(lightNum)==3){
    doLED(0,3,1,150);
    doLED(3,4,1,200);
    doLED(1,2,1,150);
    doLED(2,3,1,100);
    doLED(0,2,1,200);
    doLED(3,4,1,150);
    doLED(0,1,1,100);
    doLED(3,4,5,150);
    doLED(1,2,1,200);
    doLED(4,5,1,100);

  }
 checkButton();

  if (maxBrightness>254)
    maxBrightness=254;

  if (lightNum>3)
    lightNum=3;

  if (dLay<1)
    dLay=1;

  }
}


void doLED(int ledStart,int ledEnd,int delayTime,int bright){
  
    for (int x=1;x<bright;x++){
      for (int y=ledStart;y<ledEnd;y++) spwm(x,led[y],delayTime);

        arousalValue = analogRead(2);
        if (arousalValue < 400 && arousalValue > 0 ){
              button=1;
              lightNum+=0.01;
              return;
              
          if (arousalValue < 100){
              button=-1;
          }
        }
          arousalValue=0;
 
 
    }
    for (int x=bright;x>1;x--){
      for (int y=ledStart;y<ledEnd;y++) spwm(x,led[y],delayTime);


        arousalValue = analogRead(2);
        if (arousalValue < 400 && arousalValue > 0 ){
              button=1;
              lightNum+=0.01;
              return;
          if (arousalValue < 100){
              button=-1;
          }
        }
          arousalValue=0;
          
    }


}

void checkButton(){

  
  arousalValue = analogRead(2);
  if (arousalValue < 400 && arousalValue > 0 ){
        button=1;
        lightNum+=0.01;
    if (arousalValue < 100){
        button=-1;
    }
  }
    arousalValue=0;
  
}



void spwm(int freq,int pin,int sp){

  //on
  digitalWrite(pin,HIGH);
  delayMicroseconds(sp*freq);

  // off
  digitalWrite(pin,LOW);
  delayMicroseconds(sp*(255-freq));


} //spwm







