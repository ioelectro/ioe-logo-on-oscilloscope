/**
 * @author Liyanboy74
 * @brief  Draw IOE logo on scilloscope by Arduino
 * @version 0.1
 * @date 2023-01-05
 * @pinout
 * Pin [2,3,4,5]   -> X
 * Pin [8,9,10,11] -> Y
 */

#include <stdio.h>
#include <stdlib.h>

#define TDelayUs 2
#define DDelay   30

int i,pSize;
float p;
int sx,flip;
int xMin=-1,xMax=15;

typedef struct{
  uint8_t x,y;
}point_s;

// 16 X 16 for 4-bit X & Y
const point_s points[]={
{4,1},{4,0},{0,0},{0,1},{1,1},{1,13},{0,13},{0,14},{4,14},{4,13},{3,13},{3,1},{4,1},  // I
{9,1},{9,13},{4,13},                                                                  // O
{14,13},{14,11},{11,11},{11,8},{14,8},{14,6},{11,6},{11,3},{14,3},{14,1},{9,1},       // E
{7,3},{7,11},{5,11},{5,3},{7,3},{9,1}                                                 // o
};

const point_s ziro={0,0};
point_s *points_buffer;

void setup()
{
  pSize=sizeof(points)/sizeof(point_s);
  points_buffer=(point_s *)malloc(sizeof(points));

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
  for(j=0;j<pSize;j++)
  {
    draw_point(p[j]);
    delayMicroseconds(TDelayUs);
  }
}

void loop()
{
  for(p=0;p<314;p++)
  {
    sx=(sin(p/100)*7);
    for(i=0;i<pSize;i++)
    {
      points_buffer[i].y=points[i].y;
      points_buffer[i].x=map(points[i].x,xMin,xMax,8-sx,8+sx);
    }
    for(i=0;i<DDelay;i++)
      draw_points(points_buffer);
    draw_point(ziro);
  }
  flip = xMin;
  xMin = xMax;
  xMax = flip;
}
