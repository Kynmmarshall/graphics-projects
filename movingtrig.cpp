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
void rot(int cx, int cy, int b, int h, int angl=0){
 float angg=(float)angl*M_PI/180;
 int dx= b/2;
 int dy= h/2;
 int poin[6]={
    (-dx*cos(angg)-dy*sin(angg)+cx),
    (-dx*cos(angg)+dy*sin(angg)+cy),
    (dx*cos(angg)-dy*sin(angg)+cx),
    (dx*cos(angg)+dy*sin(angg)+cy),
    (dx*cos(angg)-dy*sin(angg)+cx),
    (-dx*cos(angg)+dy*sin(angg)+cx),

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
while(i<10000){
cleardevice();
rot(300,200,150,100,i);
i+=10;
delay(100);
}
getch();
closegraph();
return 0;
}
