  #include <graphics.h>

using namespace std;

int main()
{
    int i=0;
int gd=DETECT,gm;
initgraph(&gd,&gm,"");
while(i<100000){
circle(300,250,i);
delay(5);
i+=7;
}

getch();
closegraph();
return 0;
}
