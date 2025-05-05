#include<graphics.h>   // Graphics library for drawing
#include<math.h>       // For mathematical operations like pow, sqrt
#include <conio.h>     // For _getch(), kbhit()
#include <windows.h>   // For GetAsyncKeyState() to handle real-time keypresses
#include<random>       // For random number generation
#include<ctime>        // For seeding the random generator
#include <cstdlib>     // Standard library

//bomb class that is used by each bomb that spawns
class Bomb {
public:
   int x, y;    //bomb's position on screen
   bool active; //Is bomb showing (true) or not (false)
};

//Global variables
bool pause=false;        //Pause state
int score=0;             //player's Score
int arrax[25],array[25]; //first terrain points 
int arrx[25],arry[25];   //second terrain poins
char text[20];           //for displaying score
Bomb bombs[17];          //array of bombs
bool players=false;      //1 player(false) and 2 players(true)
int width=GetSystemMetrics(SM_CXSCREEN); //measures the width of the screen
int height=GetSystemMetrics(SM_CYSCREEN); //measures the height of the screen

// Cloud positions (x and y coordinates)
int xc=200;
int yc=20+(rand()%3)*50;
int xc2=900;
int yc2=20+(rand()%3)*50;
int xc3=1200;
int yc3=20+(rand()%3)*50;
int xc4=400;
int yc4=20+(rand()%3)*50;
int xc5=1000;
int yc5=20+(rand()%3)*50;
int xc6=700;
int yc6=20+(rand()%3)*50;
float t=0;

//Pure virtual Base class representing location and type of player(used for polymorphism).
class location{   
    public:
    int x , y , x2 , y2 ;  // Plane's core points coordinates
    bool type;             // true for yellow plane (Player 1), false for blue (Player 2)
    
        location(int x = 0, int y = 0,int x2=0,int y2=0,bool type=true) {
            this->x = x;
            this->y = y;
            this->x2=x2;
            this->y2=y2;
            this->type=type;
        }
    
        virtual void draw() = 0;  //abstract draw function for polymorphism
    };

    // Class representing a player (plane)
class playerr: public location{  //playerr class inherits the location class that helps know the position and color of the different plane
    public:
    playerr(int x=0,int y=0, int x2=0, int y2=0,bool type=true) //Overloaded constructor to initialize values for the class
      :location(x,y,x2,y2,type){}
    
    void draw() override{}
    
    // Draws the plane and handles movement
    void player(){
        int speed=15;
        if (type==true){
            setcolor(YELLOW);
        }  
        else{
            setcolor(BLUE);
        }
        
        // Draw main body of the plane and colors it
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
          if (type==true){
            setfillstyle(1,YELLOW);
            floodfill((x+x2)/2,(y+y2)/2,YELLOW);
            
            // Control using keys
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
        }  
        else{
            setfillstyle(1,BLUE);
            floodfill((x+x2)/2,(y+y2)/2,BLUE);
            if(GetAsyncKeyState(VK_UP)){
                y-=speed;
                y2-=speed;
             }
            if(GetAsyncKeyState(VK_LEFT)){
                x-=speed;
                x2-=speed;
             }
             if(GetAsyncKeyState(VK_DOWN)){
                y+=speed;
                y2+=speed;
             }
             if(GetAsyncKeyState(VK_RIGHT)){
                x+=speed;
                x2+=speed;
             }
        }
      
     
     
     if (x < 0) { x = 0; x2 = 50; }
      if (x2 > 1000) { x =1000 - 50; x2 =1000; }
      if (y < 0) { y = 0; y2 = 30; }
      if (y2 >450) { y = 450 - 30; y2 = 450; }
     
     }
    
    //player is death (true) else (false) 
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
    
       //Draws both scrolling terrain from left to right
    void terrain() {
        int i=1;
        setcolor(GREEN);
        setlinestyle(CENTER_LINE, 0,200);
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
        while(i < 24) {
            line(arrax[i], array[i], arrax[i + 1], array[i + 1]);
            line(arrx[i], arry[i], arrx[i + 1], arry[i + 1]);
            i++;
        }
        line(arrax[24], array[24], arrax[0], array[0]);
        line(arrx[24], arry[24], arrx[0], arry[0]);
     }
   
     //An overloaded function to spawn both the bombs and the clouds
    void overload(Bomb &b,int ran){
        setcolor(RED);
        if (!b.active) return;
        
         int px = b.x;
         int py = b.y; 
         circle(px, py, 15);
         if(ran<9){
         setfillstyle(SOLID_FILL, RED);
         floodfill(px, py, RED);
        }
        else{
           setfillstyle(SOLID_FILL, BLACK);
         floodfill(px, py, RED);
        }
        t+=.0009 ;
         b.x -= 10+t;
         if (b.x < 0) {
             b.active = false;
             score++;
         }
     
     }  
    void overload(int &xc, int &yc){
   
        int cloudX[6] = {xc, xc + 20, xc + 40, xc + 60, xc + 30, xc + 10};
        int cloudY[6] = {yc, yc - 10, yc, yc - 10, yc + 10, yc + 10};
        int size = sizeof(cloudX) / sizeof(cloudX[0]);
     
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        int i=0;
        while(i < size) {
            fillellipse(cloudX[i], cloudY[i], 20, 15);
            i++;
        }
       if(xc<=-90){
        xc=1300;
        yc=(rand()%3)*50;
       }
       else{
        xc-=2;
       }
     }
    
    //function to calculate distance between two points (Checks if player touching bomb)
    int distancebetween(int x,int y,Bomb &b){
        int playerx=x;
        int playery=y;
        int bombx=b.x;
        int bomby=b.y;
        int bombradius=15;
    
       return(sqrt(pow(bombx-playerx,2)+pow(bomby-playery,2)));
    }
   
    void pauses(){
     setcolor(WHITE);
     setlinestyle(1,1,10);
     settextstyle(SANS_SERIF_FONT,0,60);
     outtextxy(580, 350,"PAUSE");
     delay(10);
     }
    };

//initialize two playerr objeects for the two planes
playerr player1(30,300,80,330,true);
playerr player2(30,210,80,240,false);

//Draws the game menu
class menus{
    public:
    //method for rotating star
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
        }
   
        //draws actual menu 
    void menu(int i){
        setcolor(YELLOW);
        rectangle(400,200,900,600);
        ellipse(650,55,0,360,400,50);
        settextstyle(GOTHIC_FONT,0,60);
        outtextxy(315,34,"WELCOME TO KYNM 1.1");
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
        floodfill(318,130,YELLOW);
        setfillstyle(HATCH_FILL,LIGHTMAGENTA);
        floodfill(318,40,YELLOW);
        rectangle(550,300,750,360);
        rectangle(550,400,760,460);
        rectangle(550,500,760,560);
        settextstyle(SMALL_FONT,0,10);
        outtextxy(560,310,"1 player");
        outtextxy(551,410,"2 players");
        outtextxy(600,510,"EXIT");
        floodfill(430,210,YELLOW);
        setfillstyle(SOLID_FILL,BLUE);
      }
};

int c=0;
int main()
{
 menus menu1;
srand(time(0));
int i=0,j=0;
POINT cursorpos;
bool play=false,men=true;
initwindow(width,height,"");
  bool spawnbomb=true;
int random_number=1000,ran=15;

// when men=true shows the menu screen with all it details
while(men==true){
   cleardevice();
   menu1.menu(j); 
   GetCursorPos(&cursorpos);
    j+=10;

    //when mouse hover over the respective option it changes their color to red
    setfillstyle(SOLID_FILL,RED);
    if(550<=cursorpos.x && cursorpos.x<=750 && 328<=cursorpos.y && cursorpos.y<=388){
     floodfill(553,305,YELLOW);
     
     //when mouse button is clicked on particular places on screen program perform respective tasks
     if(ismouseclick(WM_LBUTTONDOWN)){
        play=true;
        break;
     }
    }
   
     else if(550<=cursorpos.x && cursorpos.x<=760 && 400<=cursorpos.y && cursorpos.y<=460){
      floodfill(552,403,YELLOW);
      if(ismouseclick(WM_LBUTTONDOWN)){
        players=true;
        play=true;
        break;
     }
     }
     else if(550<=cursorpos.x && cursorpos.x<=760 && 500<=cursorpos.y && cursorpos.y<=560){
      floodfill(553,505,YELLOW);
      if(ismouseclick(WM_LBUTTONDOWN)){
         return 0;
      }
     }
     swapbuffers();
 delay(100);
   
}
if(c==0){
cleardevice();
c=1;   

if(players==false){
player2.x= 3000,player2.y = 250, player2.x2 = 3050, player2.y2 = 280;
}
}
while(play==true){
    if(GetAsyncKeyState(VK_ESCAPE)){  //if Esc is pressed stop all
        return 0;
     }
  
   setbkcolor(LIGHTBLUE);
   player1.player();

   //spawn player 2 only if players=2 (2 player is clicked)
   if(players==true){
   player2.player();}

   
   player1.overload(xc,yc);
   player1.overload(xc2,yc2);
   player1.overload(xc3,yc3);
   player1.overload(xc4,yc4);
   player1.overload(xc5,yc5);
   player1.overload(xc6,yc6);

   //spawn Bombs
   if (spawnbomb) {  
      ran = (rand() % 13) + 2;
    while(i < ran) {
         bombs[i].x = (rand() % (1500)) + 1400;
         bombs[i].y = (rand() % (450 - 50)) + 25;
        bombs[i].active = true;
        i++;  
    } 
    i=0;
      spawnbomb =false;
  }     

  //spawn terrain
  player1.terrain();

  //Display user interface instruction on screen
   setcolor(YELLOW);
   setlinestyle(CENTER_LINE,0,1);
   settextstyle(SANS_SERIF_FONT, 0,80);
   outtextxy(20, 580,"pause on 'P'");
   rectangle(18,580,127,605);
   outtextxy(width-137, 580,"Exit on 'Esc'");
   rectangle(width-139,580,width-30,605);
   outtextxy(132, 580,"pause off 'O'");
   rectangle(130,580,239,605);
  setlinestyle(SOLID_LINE, 0,1);   
  bool allInactive = true;
  while(i < ran) {
  if (bombs[i].active) {
   player1.overload(bombs[i],ran);
   allInactive = false;
}

//pauses game
if(GetAsyncKeyState('P')){
    player1.pauses();
     int m=0;
while(true){    
if(m<1){
  m++;
 }
   if(GetAsyncKeyState('O')){
    break;
 }
 delay(100);
}
 }
i++;
} 
i=0;
if (allInactive){ 
   spawnbomb = true;
}
        
   sprintf(text, "score: %d",score); //store the score in text
   settextstyle(SMALL_FONT,0,10);
   setcolor(RED);
   outtextxy(20,20, text);        //prints the score on the top left of the screen
if(GetAsyncKeyState(VK_RETURN)){
   break;      
  }
  

  //checks if player(s) is touching bomb then displays gameover screen
   if(player1.isgameover(ran)==TRUE || player2.isgameover(ran)==TRUE){
   cleardevice();
   int y=0;
   while(TRUE){
      swapbuffers();  //prevents screen flashing 
      setcolor(RED);
      setbkcolor(BLACK);
      settextstyle(SANS_SERIF_FONT, 0,40);
      outtextxy(460, 300,"GAME  OVER");
      outtextxy(550,350, text);
      if(GetAsyncKeyState(VK_ESCAPE)){
        return 0;
     }
      if(players==true){
      if(player1.isgameover(ran)==true){
      outtextxy(420,400,"player blue win");}
      else{
      outtextxy(420,400,"player yellow win");}}
      setcolor(YELLOW);
      settextstyle(SANS_SERIF_FONT, 0,80);
      outtextxy(20, 50,"RESTART (press R)");
      rectangle(20,50,198,75);

      //IF R is pressed put the values of all variables to default
      if(GetAsyncKeyState('R')){
     player1.x = 50; player1.y = 430; player1.x2 = 100; player1.y2 = 460;
     if(players==true){
     player2.x = 30, player2.y = 250, player2.x2 = 80, player2.y2 = 280;}
     t=0;
     i=0;
     while(i<ran){
     bombs[i].active = false;
   i++;}
     score=0;
      cleardevice();
      break;
      }
      delay(100);
   }
}
 swapbuffers();
  delay(20); //smoothens the motions on the screen
  cleardevice(); //refreshes the screen display to simulate motion
}
getch(); 
closegraph();
return 0;
}