//class Person contains two class Legs,
// a right and left leg. the right leg 
//starts walking 20 frames later with its own timer!

//deff
int t;
boolean started;
Person [] moveMatrix=new Person [50];


//setup
void setup()
{
framerate(30);
size(700, 500);
background(255);
smooth();
strokeCap(ROUND);
strokeJoin(ROUND);
strokeWeight(10);

t=-1;
started=false;
for(int i=0; i<moveMatrix.length;i++)//Leg#, start time, y displacement, scaleValue
  moveMatrix[i] = new Person(round(random(0.5,6.4)), i, random(-50,50), random(.3,1));
}



//draw
void draw()
{
background(255);

if(mousePressed==true)
  started=true;

if(started==true && mousePressed==false)
  {
  t+=1;
  started=false;
  if(t==moveMatrix.length)
    t=-1;
  }

for(int i=0; i<moveMatrix.length;i++)
  moveMatrix[i].move(t);
  
println(t); 
  
 
  
  
}

