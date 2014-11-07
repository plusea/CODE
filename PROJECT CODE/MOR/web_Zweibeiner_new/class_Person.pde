class Person
{
Leg Lleg;
Leg Rleg;

int legNum, ln;
int timer, t; // for start time
float m, n;  //move
int st, start;  //start time
float y, ydis;
float sv, scaleValue;
boolean RWalk, startWalking;
int rs; //right start for right leg
 
   Person(int legNum, int start, float ydis, float scaleValue)
  {
  ln=legNum;
  st=start;
  y=ydis;
  sv=scaleValue;
    
  Lleg=new Leg();
  Rleg=new Leg();
  
  RWalk=false;
  startWalking=false;
  m=0;
  rs=0;
  }
  
  
  
  void move(int timer)
  {
  t=timer;
  
  if(st==t)
    startWalking=true;  //start
  
    
  if(startWalking==true)   //keep going
    {
    pushMatrix();
    rs+=1;  //counter to start right foot wlaking
    translate(0, y);      // y-displacement    
    scale(sv);
    
    if(ln==1)
      Lleg.walk1(-100-st*6 +m);
      
    if(ln==2)
      Lleg.walk2((1/sv)*(width+st*4) -m);
      
    if(ln==3)
      Lleg.walk3(-100-st*4 +n);
      
    if(ln==4)
      Lleg.walk4((1/sv)*(width+st*4) -n);
        
    if(ln==5)
      Lleg.walk5(-100-st*4 +n);
        
    if(ln==6)
      Lleg.walk6((1/sv)*(width+st*4) -n);
        
    if(rs==20)
      RWalk=true;
      
    if(RWalk==true)
      {
      if(ln==1)
        Rleg.walk1(-100-st*6 +m);
      if(ln==2)
        Rleg.walk2((1/sv)*(width+st*4) -m);
      if(ln==3)
        Rleg.walk3(-100-st*4 +n);
      if(ln==4)
        Rleg.walk4((1/sv)*(width+st*4) -n);
      if(ln==5)
        Rleg.walk5(-100-st*4 +n);
      if(ln==6)
        Rleg.walk6((1/sv)*(width+st*4) -n);
      }
    popMatrix();
    m+=6;
    n+=4;   
    } //////////////////////////////////end startWalking==true
  }
}

