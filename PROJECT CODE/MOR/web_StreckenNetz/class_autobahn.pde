class Autobahn
{
  float xs, ys, thick, angle;  //class variables
  float xstart, ystart, thickness, a;  //Line constructor variables
  float x, y, x2start, y2start, x2, y2; //update x,y positions
  float updateAngle, upa, a2, upa2, updateAngle2;  //update angles
  boolean changedAngle=false;
  int rs, randomSecond; //random second to change diretion
  int startTime, st, t, timer;
  boolean start;

  
  
  
 Autobahn(int startTime, float xs, float ys, float thick, float angle)  //deffine initial starting values of variables
  {

  st=startTime;
  xstart=xs;  
  ystart=ys;
  x2start=xs; //both lines start from same random starting point
  y2start=ys;
  thickness=thick;
  a=angle;
  a2=angle+180; //angle for take off in opposite direction
  start=false;
  }
  
  
  
 void update(int timer, float updateAngle, float updateAngle2, int randomSecond) //deffine changine variables
  {
  t=timer;
  upa=updateAngle;
  upa2=updateAngle2;
  rs=randomSecond;;

  if(st==t)  //start when called
    start=true;
    
  if(start==true) //keep running 
  {
    
  strokeWeight(thickness);
  
  x=xstart+sin(a*PI/180);
  y=ystart+cos(a*PI/180);
  
  x2=x2start+sin(a2*PI/180);
  y2=y2start+cos(a2*PI/180);
  
  line(xstart, ystart, x, y);
  line(x2start, y2start, x2, y2);
  
  xstart=x;                //set current x,y values to starting values for next line
  ystart=y;
  x2start=x2;
  y2start=y2;
  
    if(second()% rs == 0)    //time to change direction
     {
     a+=upa;
     a2+=upa2;
     }
    if(x>width+10 || x<-10)    //positions to turn around from
      a=-1*a;
    if(y>height+10 || y<-10)
      a=-1*a;
    if(x2>width+10 || x2<-10)
      a2=-1*a2;
    if(y2>height+10 || y2<-10)
      a2=-1*a2;
  }
  }
}

