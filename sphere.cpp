#include<graphics.h>
#include<math.h>
void rot(int cx,int cy,int x1, int y1,int angl=0){
 float angg=(float)angl*M_PI/180;
 while(angg<100){
 int dx1=x1/3;
 int dy1=y1/3;
 int poin[2]={
    (dx1*cos(angg)-dy1*sin(angg)+cx),
    (dx1*sin(angg)+dy1*cos(angg)+cy),

 };

circle(poin[0],poin[1],20);
  angg++;}
 angg=0;
}
int main()
{
int i=0;
int gd=DETECT,gm;
initgraph(&gd,&gm,"");
while(i<10000){
cleardevice();
rot(300,200,50,125,i);
i+=10;
delay(20);
}
getch();
closegraph();
return 0;
}
