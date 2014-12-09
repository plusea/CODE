//draw a line from a random starting point
// and expand in both directions
//mimmiking the movement of cars on the autobahn

Autobahn [] autoMatrix=new Autobahn[50];
boolean pressed;
int t;



//setup
void setup()
{
framerate(30);
size(700,500);
background(255);
smooth();
strokeJoin(ROUND);
strokeCap(ROUND);
t=0;
pressed=false;
}





//draw
void draw()
{
//(startTime,  xstart, ystart, thickness, starting angle)
if(mousePressed==true)
  pressed=true;

if(pressed==true && mousePressed==false) //without requesting mousePressed to be false too, more than one line is gereated at once
  {
  autoMatrix[t]=new Autobahn(t, mouseX, mouseY, random(1,2), random(-360,360));
  t+=1;
  pressed=false;
  
  if(t==autoMatrix.length)
    {
    t=0;
    background(255);
    }
}
   
for(int i=0; i<t; i++)  //timer, update angle1, update angle2, random second
  autoMatrix[i].update(i, random(-360,360)/framerate, random(-360,360)/framerate, int(random(1,4)));
}









