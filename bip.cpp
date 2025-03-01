#include<graphics.h>
#include<math.h>
using namespace std;

void trin(int x, int y, int angle, int length){
  float ang =(float)angle*M_PI/180;
  int i=0,a=x, b=y;

  line(x,y,x+length*cos(ang),y+length*sin(ang));
  x=x+length*cos(ang);
  y=y+length*sin(ang);
  line(x,y,x+length*cos(ang),y-length*sin(ang));
  x=x+length*cos(ang);
  y=y-length*sin(ang);
  line(a,b,x,y);
  x=x*cos(ang)-y*sin(ang);
  y=x*sin(ang)+y*cos(ang);
}
void rot(int cx,int cy,int x1, int x2, int x3, int y1,int y2,int y3 ,int angl=0){
 float angg=(float)angl*M_PI/180;
 int poin[6]={
    (x1*cos(angg)-y1*sin(angg)+cx),
    (x1*sin(angg)+y1*cos(angg)+cy),
    (x2*cos(angg)-y2*sin(angg)+cx),
    (x2*sin(angg)+y2*cos(angg)+cy),
    (x3*cos(angg)-y3*sin(angg)+cy),
    (x3*sin(angg)+y3*cos(angg)+cy),

 };
 int i=0;
 while(i<6){
    line(poin[i],poin[i+1],poin[(i+2)%6],poin[(i+3)%6]);
    i+=2;
 }
}
int main()
{
int i=0;
int gd=DETECT,gm;
initgraph(&gd,&gm,"");
while(i<100000){
//cleardevice();
rot(300,200,50,125,200,200,50,200,i);
i+=10;
delay(100);
}
getch();
closegraph();
return 0;
}
