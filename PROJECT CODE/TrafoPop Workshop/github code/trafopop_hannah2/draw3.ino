inline void draw3(float frameCount)
{
//  float s = 0.01 * (0.7 + 0.2 * sin(frameCount * 0.000827));
//  float r = 2.0 * M_PI * sin(frameCount * 0.000742);
//
//  float time = frameCount * 0.002;
//
//  float sinr = sin(r);
//  float cosr = cos(r);
//
//  CGPoint center1 = CGPointMake(cos(time), cos(time*0.535));
//  CGPoint center2 = CGPointMake(cos(time*0.259), cos(time*0.605));
//
  for (byte i = 0; i < NUM; i++)
  {
//    float x0 = s * normalizedX(i);
//    float y0 = s * normalizedY(i);
//    float x = (x0*cosr - y0*sinr);
//    float y = (x0*sinr + y0*cosr);
//
//    CGPoint position =
//    {
//      x,y
//    };
//
//    int size = 64;
//    float d = distance(position, center1)*size;
//    CGPoint color = CGPointMake(cos(d+time),sin(d));
//
//    CGPoint ncolor = normalize(color);
//
//    float red = ncolor.x*ncolor.x;
//    float green = ncolor.x*ncolor.y;
//    float blue = ncolor.x-ncolor.y;


      float red = fadeCount;
      float blue = fadeCount;
      float green = fadeCount;


      struct color color2 =
      {
        
        
        max(0,red * 255), max(0,green * 255), max(0,blue * 255)
        };

        pixels[i] = color2;
    }


    if(fadeCount < 1) fadeAmount = +1;
    if(fadeCount > 253) {
      fadeAmount = -1;
      delay(1000);
    }
    delay(5);

    fadeCount+=fadeAmount;
    
}

