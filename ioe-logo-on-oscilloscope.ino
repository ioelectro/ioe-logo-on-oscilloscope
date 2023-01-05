#include <stdio.h>

int i;

float p;
int sx,xMin=-1,xMax=14,flip;

typedef struct{
  uint8_t x,y;
}point_s;

const point_s points[]={
{4,1},{4,0},{0,0},{0,1},{1,1},{1,13},{0,13},{0,14},{4,14},{4,13},{3,13},{3,1},{4,1},  // I
{9,1},{9,13},{4,13},                                                                  // O
{14,13},{14,11},{11,11},{11,8},{14,8},{14,6},{11,6},{11,3},{14,3},{14,1},{9,1},       // E
{7,3},{7,11},{5,11},{5,3},{7,3},{9,1}                                                 // o
};

point_s ziro={0,0};

point_s points_buffer[33];

void setup()
{
  DDRB=0xff;
  DDRD=0xff;
}

void draw_point(point_s point)
{
  PORTB=(point.x&0xf);
  PORTD=((point.y&0xf)<<2);
}

void draw_points(point_s *p)
{
  int j;
  for(j=0;j<33;j++)
  {
    draw_point(p[j]);
    delayMicroseconds(2);
  }
}

void loop()
{
  for(p=0;p<314;p++)
  {
    sx=(sin(p/100)*7);
    for(i=0;i<33;i++)
    {
      points_buffer[i].y=points[i].y;
      points_buffer[i].x=map(points[i].x,xMin,xMax,8-sx,8+sx);
    }
    for(i=0;i<30;i++)
      draw_points(points_buffer);
    draw_point(ziro);
  }
  flip = xMin;
  xMin = xMax;
  xMax = flip;
}
