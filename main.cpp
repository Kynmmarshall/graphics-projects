#include<graphics.h>

int main()
{
initwindow(720,500,"kynm projects");
//setbkcolor(WHITE);
//cleardevice();
//setcolor(GREEN);
circle(100,100,10);
setfillstyle(SOLID_FILL,RED);
floodfill(100,100,YELLOW);
getch();
closegraph();
//return 0;
}
