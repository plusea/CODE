inline void draw2(float frameCount)
{
  float s = 0.01 * (0.7 + 0.2 * sin(frameCount * 0.000827));
  float r = 2.0 * M_PI * sin(frameCount * 0.000742);

  float time = frameCount * 0.002;

  float sinr = sin(r);
  float cosr = cos(r);

  CGPoint center1 = CGPointMake(cos(time), cos(time*0.535));
  CGPoint center2 = CGPointMake(cos(time*0.259), cos(time*0.605));
  // CGPoint center3 = CGPointMake(cos(time*0.346), cos(time*0.263));
  // CGPoint center4 = CGPointMake(cos(time*0.1346), cos(time*0.1263));
  // float size = (sin(time*0.1)+1.2)*64.0;

  for (byte i = 0; i < NUM; i++)
  {
    float x0 = s * normalizedX(i);
    float y0 = s * normalizedY(i);
    float x = (x0*cosr - y0*sinr);
    float y = (x0*sinr + y0*cosr);

    CGPoint position =
    {
      x,y
    };

    int size = 64;
    float d = distance(position, center1)*size;
    CGPoint color = CGPointMake(cos(d),sin(d));
    d = distance(position, center2)*size;
    color.x += cos(d);
    color.y += sin(d);
    /*
    d = distance(position, center3)*size;
     color.x += cos(d);
     color.y += sin(d);
     d = distance(position, center4)*size;
     color.x += cos(d);
     color.y += sin(d);
     */
    float c = sqrt(color.x*color.x+color.y*color.y)*0.25;
    // float c = (color.x*color.x+color.y*color.y);

    CGPoint ncolor = normalize(color);
    /*
    float red = c * ncolor.x;
     float green = c * ncolor.y;
     float blue = c * (-ncolor.x-ncolor.y);
     */
    float red = ncolor.x;
    float green = ncolor.y;
    float blue = c * (ncolor.x-ncolor.y);
    /*
  red = cos(red*3.0+0.5)+sin(red*2.0);
     green = cos(green*3.0+0.5)+sin(green*2.0);
     blue = cos(blue*3.0+0.5)+sin(blue*2.0);
     */
    struct color color2 =
    {
      max(0,red * 255), max(0,green * 255), max(0,blue * 255)
      };

      pixels[i] = color2;
  }
}
