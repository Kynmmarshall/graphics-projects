#include<graphics.h>
#include<math.h>
#include <conio.h>
#include <windows.h>
#include<random>
#include<ctime>
#include <cstdlib>
#include<iostream>

struct Bomb {
   int x, y;
   float angle;
   bool active;
};
struct terr {
   int x, y;
   bool active;
};
int x = 30, y = 300, x2 = 80, y2 = 330;
bool pause=false; 
int score=0;
int arrax[25];
int array[25];
int arrx[25];
int arry[25];
char text[20];
Bomb bombs[6];
terr terra[40];
void cloud(){
   int xc=1700;
   int yc=(rand()%10)*10;
   int cloudX[6] = {xc, xc + 20, xc + 40, xc + 60, xc + 30, xc + 10};
   int cloudY[6] = {y, y - 10, y, y - 10, y + 10, y + 10};
   int size = sizeof(cloudX) / sizeof(cloudX[0]);

   setcolor(WHITE);
   setfillstyle(SOLID_FILL, WHITE);
   int i=0;
   while(i < size) {
       fillellipse(cloudX[i], cloudY[i], 20, 15);
       i++;
   }
 // while(xc>=0){
  // xc--;
 // }
}
void stars(int centerX, int centerY, int size,int angle){
      float rad=(float)angle*(M_PI / 180);
      int arra[8],arrar[8];
          arra[0] = centerX +size *sin(rad);
          arrar[0] = centerY - size * cos(rad);

          arra[1] = centerX + size/4 * cos(rad)- size/5 * sin(rad);
          arrar[1] = centerY + size/4 * sin(rad)+ size/5 * cos(rad);
          
          arra[2]= centerX + size * cos(rad);
          arrar[2] = centerY + size * sin(rad);

          arra[3] = centerX + size/4 * cos(rad)+ size/5 * sin(rad);
          arrar[3] = centerY + size/4 * sin(rad)- size/5 * cos(rad);
          
          arra[4] = centerX - size * sin(rad);
          arrar[4] = centerY + size * cos(rad);
          
          arra[5] = centerX - size/4 * cos(rad)+ size/5 * sin(rad);
          arrar[5] = centerY - size/4 * sin(rad)- size/5 * cos(rad);
          
          arra[6] = centerX - size * cos(rad);
          arrar[6] = centerY - size * sin(rad) ;
          
          arra[7] = centerX - size/4 * cos(rad)- size/5 * sin(rad);
          arrar[7] = centerY - size/4 * sin(rad) + size/5 * cos(rad);

          setcolor(YELLOW);
          int i=0;
          while(i<7){
          line(arra[i], arrar[i], arra[i+1], arrar[i+1]);
           i++; 
         }
         line(arra[7],arrar[7],arra[0],arrar[0]);
          //delay(20); 
          angle += 10;
      }
void menu(int i){
  setcolor(YELLOW);
  rectangle(400,200,900,600);
  ellipse(650,55,0,360,400,50);
  settextstyle(GOTHIC_FONT,0,60);
  outtextxy(315,34,"WELCOME TO KYNM 1.0");
  setfillstyle(SOLID_FILL,YELLOW);
  stars(50,100,20,i);
  floodfill(50,100,YELLOW);
  stars(100,50,30,i);
  floodfill(100,50,YELLOW);
  stars(150,100,20,i);
  floodfill(150,100,YELLOW);

  stars(1100,100,20,i);
  floodfill(1100,100,YELLOW);
  stars(1150,50,30,i);
  floodfill(1150,50,YELLOW);
  stars(1200,100,20,i);
  floodfill(1200,100,YELLOW);

  setfillstyle(XHATCH_FILL,CYAN);
  floodfill(1900,20,YELLOW);
  setfillstyle(HATCH_FILL,LIGHTMAGENTA);
  floodfill(318,34,YELLOW);
  rectangle(550,300,750,360);
  rectangle(480,400,800,480);
  rectangle(550,500,760,560);
  settextstyle(SMALL_FONT,0,10);
  outtextxy(560,310,"START");
  outtextxy(490,420,"HIGH SCORE");
  outtextxy(600,510,"EXIT");
  floodfill(430,210,YELLOW);
  setfillstyle(SOLID_FILL,BLUE);
}
int distancebetween(int x,int y,Bomb &b){
    int playerx=x;
    int playery=y;
    int bombx=b.x;
    int bomby=b.y;
    int bombradius=15;

   return(sqrt(pow(bombx-playerx,2)+pow(bomby-playery,2)));
}
void triangle(int x1,int y1,int x2,int y2,int x3,int y3){
   moveto(x1,y1);
   lineto(x2,y2);
   lineto(x3,y3);
   line(x1,y1,x3,y3);
}
void player(){
   
      int speed=15;
     
      //cleardevice();  
   setcolor(YELLOW);
        circle(x2+2,y+7,3);
        circle(x2+2,y+21,3);
        line(x, y+15, x-20, y+40);  
        line(x + 30, y, x, y - 50);   
        line(x, y - 50, x2, y);           
        line(x2 - 20, y2, x, y2 + 50); 
        line(x, y2 + 50, x2, y2);
        line(x, y, x-20, y-10);           
        line(x, y+15, x -20, y - 10); 
        line(x, y2, x - 20, y + 40); 
        arc(x2, y2 - 15, 270, 90, 15);
        line(x, y, x+30, y);
        line(x, y2, x+30, y2);
   setfillstyle(1,YELLOW);
   floodfill((x+x2)/2,(y+y2)/2,YELLOW);
   if(GetAsyncKeyState('W')){
      y-=speed;
      y2-=speed;
   }
   if(GetAsyncKeyState('A')){
      x-=speed;
      x2-=speed;
   }
   if(GetAsyncKeyState('S')){
      y+=speed;
      y2+=speed;
   }
   if(GetAsyncKeyState('D')){
      x+=speed;
      x2+=speed;
   }

   if (x < 0) { x = 0; x2 = 50; }
    if (x2 > 1000) { x =1000 - 50; x2 =1000; }
    if (y < 0) { y = 0; y2 = 30; }
    if (y2 >450) { y = 450 - 30; y2 = 450; }

}
void bombb(Bomb &b,int ran){
   if (!b.active) return;
    float rad = b.angle * M_PI / 180.0;
    int dx = cos(rad); 
    int dy = sin(rad);

    int px = b.x + dx;
    int py = b.y + dy;

    setcolor(RED);
    circle(px, py, 15);
    if(ran<9){
    setfillstyle(SOLID_FILL, RED);
    floodfill(px, py, RED);
   }
   else{
      setfillstyle(SOLID_FILL, BLACK);
    floodfill(px, py, RED);
   }
    b.x -= 10;
    b.angle += 10;
    if (b.x < 0) {
        b.active = false;
        score++;
    }

}  
void terrain() {
   int i=1;
   static bool initialized = false;
   if (!initialized) {
       while(i < 24) {
           arrax[i] = (i * 50);  
           array[i] = (rand() % 100) + 600;
           arrx[i] = (i * 50)+1300;  
           arry[i] = (rand() % 100) + 600;
           i++;
       }
           arrax[24]=1300;
           array[24]=630;
           arrax[0]=0;
           array[0]=630;
           arrx[24]=2600;
           arry[24]=630;
           arrx[0]=1300;
           arry[0]=630;
       initialized = true;
   }
   
   i=0;
   while(i <= 24) {
       arrax[i] -= 5; 
       arrx[i] -= 5;
       i++;
   }
   setcolor(GREEN);
   if(arrax[24]<=0){
      i=1;   
      while(i < 24) {
         arrax[i] = (i * 50)+1300; 
         array[i] = (rand() % 100) + 600; 
         i++;}
         arrax[0]=1300;
         array[0]=630;
         arrax[24]=2600;
         array[24]=630;
     }
     if(arrx[24]<=0){
      i=1;
      while(i < 24) {
         arrx[i] = (i * 50)+1300; 
         arry[i] = (rand() % 100) + 600; 
         i++;
     }
         arrx[0]=1300;
         arry[0]=630;
         arrx[24]=2600;
         arry[24]=630;
     }
     
   i=0;
   setlinestyle(CENTER_LINE, 0,200);
   while(i < 24) {
       line(arrax[i], array[i], arrax[i + 1], array[i + 1]);
       line(arrx[i], arry[i], arrx[i + 1], arry[i + 1]);
       i++;
   }
   line(arrax[24], array[24], arrax[0], array[0]);
   line(arrx[24], arry[24], arrx[0], arry[0]);
}
bool isgameover(int ran){
   int i=0,j=0;
   int bombradius=15;
   while(i < ran) {
      if (bombs[i].active) {
          int distances[] = {
              distancebetween(x, y + 15, bombs[i]),
              distancebetween(x - 20, y + 40, bombs[i]),
              distancebetween(x + 30, y, bombs[i]),
              distancebetween(x, y - 50, bombs[i]),
              distancebetween(x2, y, bombs[i]),
              distancebetween(x2 - 20, y2, bombs[i]), 
              distancebetween(x, y, bombs[i]),
              distancebetween(x, y2 + 50, bombs[i]),
              distancebetween(x - 20, y - 10, bombs[i]),
              distancebetween(x - 20, y + 40, bombs[i]),
              distancebetween(x2 + 7, y2 - 11, bombs[i]),
              distancebetween(x + 25, y-20, bombs[i]),
              distancebetween(x + 30, y2, bombs[i]),
              distancebetween(x + 25, y2+20, bombs[i])         
            };
             j=0;
          while(j<14) {
              if (distances[j] <= bombradius-5) {
                  return true;
              }
              j++;
          }
        
      } i++;
  }
  return false;}
void pauses(){
   setcolor(WHITE);
settextstyle(SANS_SERIF_FONT,0,60);
outtextxy(580, 350,"PAUSE");
}

int main()
{
srand(time(0));
int i=0,j=0;
POINT cursorpos;
bool play=false,men=true;
initwindow(1920,640,"kynm windows");
  bool spawnbomb=true;
int random_number=1000,ran=5;
//int arrax[7]={10,20,30,40,50,60,70},arrax2[7]={20,30,40,50,60,70,80},arrame[17];
while(men==true){
   cleardevice();
   menu(j); 
   GetCursorPos(&cursorpos);
    j+=3;
    setfillstyle(SOLID_FILL,RED);
    if(550<=cursorpos.x && cursorpos.x<=750 && 328<=cursorpos.y && cursorpos.y<=388){
     floodfill(553,305,YELLOW);
     if(ismouseclick(WM_LBUTTONDOWN)){
        play=true;
        break;
     }
    }
    else if(480<=cursorpos.x && cursorpos.x<=800 && 400<=cursorpos.y && cursorpos.y<=480){
      floodfill(483,405,YELLOW);
      if(ismouseclick(WM_LBUTTONDOWN)){
      
      }
     }
     else if(550<=cursorpos.x && cursorpos.x<=760 && 500<=cursorpos.y && cursorpos.y<=560){
      floodfill(553,505,YELLOW);
      if(ismouseclick(WM_LBUTTONDOWN)){
         break;
      }
     }
 delay(50);
   
}
cleardevice();
while(play==true){
   if(GetAsyncKeyState('P')){
      pause=true;
   }
   int m=0;
   while(pause==true){    
      if(m<1){
       pauses();
       m++;
      }
        if(GetAsyncKeyState('O')){
         pause=false;
         break;
      
      }
   }
   cloud();
   setbkcolor(LIGHTBLUE);
   player();
   if (spawnbomb) {
      ran = (rand() % 15) + 2;  
    while(i < ran) {
         bombs[i].x = (rand() % (2000)) + 1900;
         bombs[i].y = (rand() % (450 - 50)) + 25;
         bombs[i].angle = rand() % 360;
        bombs[i].active = true;
        i++;  
        //delay(rand()%100);
    } 
    i=0;
      spawnbomb =false;
  }     
  terrain();
  setlinestyle(SOLID_LINE, 0,1);
     bool allInactive = true;
        while(i < ran) {
            if (bombs[i].active) {
                bombb(bombs[i],ran);
                allInactive = false;
            }
            if(bombs[i].active==true){
               score;
              }
            i++;
        } 
        i=0;
        if (allInactive) spawnbomb = true;
        
sprintf(text, "score: %d",score);
   settextstyle(SMALL_FONT,0,10);
   setcolor(RED);
   outtextxy(20,20, text);
if(GetAsyncKeyState(VK_RETURN)){
   break;      
  }
  
  if(isgameover(ran)==TRUE){
   break;}
  delay(20);
  cleardevice();
}
cleardevice();
setbkcolor(BLACK);
settextstyle(SANS_SERIF_FONT, 0,40);
outtextxy(460, 300,"GAME  OVER");
delay(10000);
getch();
closegraph();
return 0;
}