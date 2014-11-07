class Leg
{
float xk, yk, xf, yf;
float a, b, c, d;
int t;
float move, m;
float speed, s;



  Leg()
  {
  xk=0;
  yk=80;
  xf=0;
  yf=160;
  t=0;
  m=-100;
  }
  
  
  
  void walk1(float move)
  {
  m=move;
  pushMatrix();
  translate(m, height/2);
  beginShape(LINE_STRIP); 
  vertex(0, 0); 
  vertex(xk, yk); 
  vertex(xf, yf); 
  endShape();
  popMatrix();
  xk+=a;
  yk+=b;
  xf+=c;
  yf+=d;
  if(t<10)
    {
    a=-3;
    b=0;
    c=-6;
    d=0;
    }
  if(t==10)
    {
    a=8;
    b=-1;
    c=4;
    d=-4;
    }
  if(t==20)
    {
    a=-2;
    b=1;
    c=8;
    d=4;
    }
  if(t==30)
    {
    a=-3;
    b=0;
    c=-6;
    d=0;
    }
  if(t==40)
    t=0;
  t+=1;
  }
  
  
  
  
  
  
  
  void walk2(float move)
  {
  m=move;
  pushMatrix();
  translate(m, height/2);
  beginShape(LINE_STRIP); 
  vertex(0, 0); 
  vertex(xk, yk); 
  vertex(xf, yf); 
  endShape();
  popMatrix();
  xk-=a;
  yk+=b;
  xf-=c;
  yf+=d;
  if(t<10)
    {
    a=-3;
    b=0;
    c=-6;
    d=0;
    }
  if(t==10)
    {
    a=8;
    b=-1;
    c=4;
    d=-4;
    }
  if(t==20)
    {
    a=-2;
    b=1;
    c=8;
    d=4;
    }
  if(t==30)
    {
    a=-3;
    b=0;
    c=-6;
    d=0;
    }
  if(t==40)
    t=0;
  t+=1;
  } 
  
 
  
   
    
     void walk3(float move)
  {
  m=move;
  pushMatrix();
  translate(m, height/2);
  beginShape(LINE_STRIP);////////////////////////////////LEG
  vertex(0, 0); 
  vertex(xk, yk); 
  vertex(xf, yf); 
  endShape();
  popMatrix();
  xk+=a;
  yk+=b;
  xf+=c;
  yf+=d;  
  if(t<10)
    {
    a=-2;
    c=-4;
    }
  if(t==10)
    {
    a=4;
    c=4;
    }
  if(t==20)
    {
    a=0;
    c=4;
    }
  if(t==30)
    {
    a=-2;
    c=-4;
    }
  if(t==40)
    t=0;
  t+=1;
  } 
  
  
  
  
  
  
  void walk4(float move)
  {
  m=move;
  pushMatrix();
  translate(m, height/2);
  beginShape(LINE_STRIP);////////////////////////////////LEG
  vertex(0, 0); 
  vertex(xk, yk); 
  vertex(xf, yf); 
  endShape();
  popMatrix();
  xk-=a;
  yk+=b;
  xf-=c;
  yf+=d;  
  if(t<10)
    {
    a=-2;
    c=-4;
    }
  if(t==10)
    {
    a=4;
    c=4;
    }
  if(t==20)
    {
    a=0;
    c=4;
    }
  if(t==30)
    {
    a=-2;
    c=-4;
    }
  if(t==40)
    t=0;
  t+=1;
  }
  
  
  
  
  
  
  
  
    void walk5(float move)
  {
  m=move;
  pushMatrix();
  translate(m, height/2);
  beginShape(LINE_STRIP); 
  vertex(0, 0); 
  vertex(xk, yk); 
  vertex(xf, yf); 
  endShape();
  popMatrix();
  xk+=a;
  yk+=b;
  xf+=c;
  yf+=d;
  if(t<10)
    {
    a=-2;
    b=0;
    c=-4;
    d=0;
    }
  if(t==10)
    {
    a=4;
    b=-1;
    c=4;
    d=-2;
    }
  if(t==20)
    {
    a=0;
    b=1;
    c=4;
    d=2;
    }
  if(t==30)
    {
    a=-2;
    b=0;
    c=-4;
    d=0;
    }
  if(t==40)
    t=0;
  t+=1;
  }
  
  
  
  
  
  
  
  
  
  void walk6(float move)
  {
  m=move;
  pushMatrix();
  translate(m, height/2);
  beginShape(LINE_STRIP); 
  vertex(0, 0); 
  vertex(xk, yk); 
  vertex(xf, yf); 
  endShape();
  popMatrix();
  xk-=a;
  yk+=b;
  xf-=c;
  yf+=d;
  if(t<10)
    {
    a=-2;
    b=0;
    c=-4;
    d=0;
    }
  if(t==10)
    {
    a=4;
    b=-1;
    c=4;
    d=-2;
    }
  if(t==20)
    {
    a=0;
    b=1;
    c=4;
    d=2;
    }
  if(t==30)
    {
    a=-2;
    b=0;
    c=-4;
    d=0;
    }
  if(t==40)
    t=0;
  t+=1;
  }
  
  
  
  
  
}

