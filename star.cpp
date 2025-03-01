#include<graphics.h>
#include<math.h>

int main()
{
int i=0;
int gd=DETECT,gm;
initgraph(&gd,&gm,"");

moveto(200,100);
linerel(50,-100);
linerel(50,100);
linerel(100,0);
linerel(-100,50);
linerel(50,100);
linerel(-100,-70);
moveto(200,100);
linerel(-100,0);
linerel(100,50);
linerel(-50,100);
linerel(100,-70);


getch();
closegraph();
return 0;
}
