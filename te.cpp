#include<graphics.h>
#include<random>
#include<ctime> 
int x=50,y=340,x1=150,z=370;
//int arr1[7]={y,y,y,y,y,y,y},arra1[7]={y1,y1,y1,y1,y1,y1,y1};
int arr[7],arra[7];
int main(){
    bool play=true;
    initwindow(500,500,"hello");
  int j=1, i=0,k=0;
  while(play){
    cleardevice();
    setfillstyle(1,COLOR(70,45,20));
    bar(30,30,50,400);
  srand(time(0));
  arr[0]=y;
  arra[0]=z;
  j=1;
  while(j<7){
  arr[j]=y+(rand()%10);
    arra[j]=z+(rand()%10);
    j++;
  }
  k=x;
      i=0;
  while(i<5){
    line(k,arr[i],k+16,arr[i+1]);
    line(k,arra[i],k+16,arra[i+1]);
    k+=16;
    i++;
  } 
  line(k,arr[5],x1,arr[6]);
  line(k,arra[5],x1,arra[6]);
  line(x1,arr[6],x1,arra[6]);
  line(x,arr[0],x,arra[0]);
  line(x+33,arr[2],x+33,arra[2]);
  line(x+66,arr[4],x+66,arra[4]);
  setfillstyle(1,GREEN);
  floodfill(52,y+10,WHITE);
  floodfill(148,y+10,WHITE);
  setfillstyle(1,WHITE);
  floodfill(100,y+10,WHITE);
  if(y>30){
  y-=.5;
  z-=.5;}
  delay(1);
}
  getch();
  closegraph();
    return 0;
}