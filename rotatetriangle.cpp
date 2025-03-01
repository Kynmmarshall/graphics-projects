#include<graphics.h>
#include<math.h>
void rot(int cx,int cy,int hit,int base,int angl=0){
 float angg=(float)angl*M_PI/180;
 int dx=base/2;
 int dy=hit/2;
 int poin[6]={
     /* taking the distance between the vertices(bou pointure) and the center of the figure

     ie x1=-dx   y1=dy  x2=0 y2=-dy  x3=dx y3=dy  */

    (-dx*cos(angg)+dy*sin(angg)+cx),
    (-dx*sin(angg)-dy*cos(angg)+cy),
    (-dy*sin(angg)+cx),
    (dy*cos(angg)+cy),
    (dx*cos(angg)+dy*sin(angg)+cx),
    (dx*sin(angg)-dy*cos(angg)+cy),

 };
    line(poin[0],poin[1],poin[2],poin[3]);
    line(poin[0],poin[1],poin[4],poin[5]);
    line(poin[2],poin[3],poin[4],poin[5]);
}
int main()
{
int i=0;
int gd=DETECT,gm;
initgraph(&gd,&gm,"");
while(i<10000){
cleardevice();
rot(300,200,100,125,i);
i+=10;
delay(50);
}
getch();
closegraph();
return 0;
}
