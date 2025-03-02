#include<graphics.h>
#include<math.h>
void rot(int cx,int cy,int x1, int y1,int angl=0){
 float angg=(float)angl*M_PI/180;
 while(angg<200){
 int dx1=x1;
 int dy1=y1;
 int poin[2]={
    (dx1*cos(angg)-dy1*sin(angg)+cx),
    (dx1*sin(angg)+dy1*cos(angg)+cy),

 };
setcolor(BROWN);
circle(poin[0],poin[1],70);
setfillstyle(6,YELLOW);
floodfill(poin[0],poin[1],BROWN);
  angg+=1;}
 angg=0;
}
int main()
{
int i=0;

initwindow(720,500,"kynm window");
setbkcolor(WHITE);
cleardevice();
readimagefile("im.jpg",100,50,400,400);
setcolor(BLACK);
settextstyle(4,HORIZ_DIR,6);
outtextxy(20,40,"TA GROSSE TETE");
//rot(300,220,50,125,i);
i++;
getch();
closegraph();
return 0;
}
