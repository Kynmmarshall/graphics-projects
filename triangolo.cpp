#include<graphics.h>
#include<math.h>
using namespace std;

void trin(int x, int y, int angle, int length){
  float ang =(double)angle*M_PI/180;
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
int main()
{
int i=0;
int gd=DETECT,gm;
initgraph(&gd,&gm,"");
while(i<10000){
trin(300,200,i,100);
i+=10;
delay(100);
}
getch();
closegraph();
return 0;
}
