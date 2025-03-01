#include<graphics.h>
#include<math.h>
void rot(int cx,int cy,int x1, int x2, int x3, int y1,int y2,int y3 ,int angl=0){
 float angg=(float)angl*M_PI/180;
 while(angg<100){
 int dx1=x1/3;
 int dx2=x2/3;
 int dx3=x3/3;
 int dy1=y1/3;
 int dy2=y2/3;
 int dy3=y3/3;
 int poin[6]={
    (dx1*cos(angg)-dy1*sin(angg)+cx),
    (dx1*sin(angg)+dy1*cos(angg)+cy),
    (dx2*cos(angg)-dy2*sin(angg)+cx),
    (dx2*sin(angg)+dy2*cos(angg)+cy),
    (dx3*cos(angg)-dy3*sin(angg)+cy),
    (dx3*sin(angg)+dy3*cos(angg)+cy),

 };
 int i=0;
 while(i<6){
        if(i<2){
            setcolor(GREEN);}
        else if(1<i<4){
            setcolor(YELLOW);
        }
        else if(i>4){
            setcolor(RED);
        }
    line(poin[i],poin[i+1],poin[(i+2)%6],poin[(i+3)%6]);
    i+=2;
 }
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
rot(300,200,50,125,200,200,50,200,i);
i+=10;
delay(20);
}
getch();
closegraph();
return 0;
}
