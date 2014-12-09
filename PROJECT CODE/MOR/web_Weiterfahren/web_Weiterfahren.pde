//parts of objects dashing by, in incomplete lines sometimes randomly connecting.
//the faster you move the mouse (simulating camera vision on a traveling crowd) the slower the motion!

//deff
Motion [] partsMatrix = new Motion[100];//start time, part, speed, distance
 
float commonSpeed, move, mx, my;
int timer, maxtime; // for start time



//setup
void setup()
{
framerate(30);
size(700, 500);
background(255);

commonSpeed=1;
timer=0;
move=0;
maxtime=1000;

for(int i=0; i<partsMatrix.length;i++)//startTime, part,personalSpeed, Ydistance, strokeWeight
    partsMatrix[i]=new Motion(int(random(maxtime)), round(random(-0.5,9.4)), random(10,20), random(1,2), random(0.1,1));

}



//draw
void draw()
{
background(255);
strokeJoin(ROUND);
strokeCap(ROUND);
smooth();

for(int i=1; i<partsMatrix.length;i++)
  partsMatrix[i].update(timer, move);
  
timer+=1;

mx=pmouseX - mouseX;
my=pmouseY - mouseY;
move=( betragVon(mx) + betragVon(my) ) / 20;

if(timer==maxtime)
  {
  timer=0;
  }
}

