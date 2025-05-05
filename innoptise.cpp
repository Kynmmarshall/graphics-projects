  #include <graphics.h>

using namespace std;

int main()
{
    int i=0;
initwindow(1300,700,"");
while(i<100000){
circle(680,350,i);
delay(5);
i+=7;
}

getch();
closegraph();
return 0;
}
