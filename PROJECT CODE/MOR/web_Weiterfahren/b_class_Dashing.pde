class Motion
{
  int part, p;
  float personalSpeed, ps;
  float commonSpeed, cs;
  float move, m, s;
  float Ydistance, yd;
  float strokeW, sw; //stroke weight
  int stime, st, timer, t; //starting time
  boolean startDashing;

  Motion (int stime, int part, float personalSpeed, float Ydistance, float strokeW)
  {
    st=stime;
    p=part;
    ps=personalSpeed;
    yd=Ydistance;
    sw=strokeW;
    startDashing=false;
  }




  void update(int timer, float move)
  { 
  m=-move;
  t=timer;
  
  if(t==0)
    {
    s=0;
    cs=0;
    startDashing=false;
    }
      
  if(st==t)
    startDashing=true;
  if(startDashing==true)
    {
    s+=ps;  //personal speed
    cs+=m;  //common speed (influenced by mouse-movement)
    
    pushMatrix();
    translate(-(200*yd)+s+cs, (height/2)-yd*50);  //move to middle and up or down
    scale(5*yd);
    strokeWeight(sw);

    if(p==0)
      {
      pushMatrix();
      beginShape(LINE_STRIP); //GOLF FRONT
      vertex(0, 0); 
      bezierVertex(3,0, 8,4, 12,7); //window
      vertex(12,7);
      bezierVertex(21,8, 29,12, 29,14); //bonnet
      vertex(29,14);
      bezierVertex(29,17, 28,19, 26,19); //bumper
      vertex(26,19); //underneeth
      vertex(23,19);
      endShape();
      popMatrix();
      }
    if(p==1)
      {
      pushMatrix();
      line(-21,0, 0,0); //GOLF TOP
      popMatrix();
      }
    if(p==2)
      {
      pushMatrix();
      beginShape(LINE_STRIP); //GOLF REAR
      vertex(0,0);
      bezierVertex(-22,0, -26,6, -26.5,7);
      vertex(-26.5,7);
      vertex(-26.5,9);
      bezierVertex(-27,9, -29,16, -23,16);
      endShape();
      popMatrix();
      }  
    if(p==3)
      {
      pushMatrix();
      beginShape(LINE_STRIP);  //BEATLE FRONT
      vertex(0,0);
      bezierVertex(7,0, 11,2, 18,7);
      vertex(18,7);
      bezierVertex(23,7, 31,11, 31,14);
      vertex(31,14);
      bezierVertex(31,18, 31,18, 26,18);
      endShape();
      popMatrix();
      }
    if(p==4)
      { 
      pushMatrix();
      beginShape(LINE_STRIP);  //BEATLE REAR
      vertex(0,0);
      bezierVertex(-8,0, -14,3, -21,9);
      vertex(-21,9);
      bezierVertex(-22,9, -23,10, -23,11);
      vertex(-23,11);
      bezierVertex(-24,12, -25,13, -25,15);
      vertex(-25,15);
      bezierVertex(-25,17, -25, 17, -21, 17);
      endShape();
      popMatrix();
      }
    if(p==5)
      {
      pushMatrix();
      line(-40,0, 0,0);
      popMatrix();
      }
    if(p==6)
      {
      pushMatrix();
      line(-10,0, 0,0);
      popMatrix();
      }
    if(p==7)
      {
      pushMatrix();
      beginShape(LINE_STRIP);  //BUS FRONT
      translate(0, -10);
      vertex(0,0);
      bezierVertex(1,0, 3,1, 3,2);
      vertex(3,2);
      vertex(3,16);
      bezierVertex(4,16, 4,17, 4,18);
      vertex(4,18);
      bezierVertex(6,18, 6,18, 6,22);
      vertex(6,22);
      bezierVertex(6,28, 6,28, -1,28);
      vertex(-1,28);
      vertex(-13,28);
      bezierVertex(-13,21, -21,21, -21,28);
      vertex(-24,28);
      endShape();
      popMatrix();
      }
    if(p==8)
      {
      pushMatrix();
      beginShape(LINE_STRIP);  //BUS REAR
      translate(0,-10);
      vertex(0,0);
      vertex(0,26);
      bezierVertex(0,28, 0,28, 2,28);
      vertex(2,28);
      vertex(34,28);
      bezierVertex(34,21, 42,21, 42,28);
      vertex(42,28);
      vertex(45,28);
      endShape();
      popMatrix();
      }
    if(p==9)
      {
      pushMatrix();  //TELEGRAPH POLE 1
      translate(0, -20);
      line(0,0, 0,60);
      line(-4,2, 4,0);
      line(-12,8, 16,2);
      popMatrix();
      }
    if(p==11)
      {
      pushMatrix();
      beginShape(LINE_STRIP);  //EMPTY
      endShape();
      popMatrix();
      }
    popMatrix();
    }
  }
}

