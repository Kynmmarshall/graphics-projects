#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <random>
#include <ctime>
#include <cstdlib>

struct Bomb {
   int x, y;
   float angle;
   bool active;
};

// Player coordinates
int x = 30, y = 300, x2 = 80, y2 = 330;
Bomb bombs[6];  // Global bomb array

int distancebetween(int x, int y, Bomb &b) {
    return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2));
}

void player() {
    int speed = 15;
    setcolor(YELLOW);

    // Player body
    circle(x2 + 2, y + 7, 3);
    circle(x2 + 2, y + 21, 3);
    line(x, y + 15, x - 20, y + 40);  
    line(x + 30, y, x, y - 50);   
    line(x, y - 50, x2, y);           
    line(x2 - 20, y2, x, y2 + 50); 
    line(x, y2 + 50, x2, y2);
    line(x, y, x - 20, y - 10);           
    line(x, y + 15, x - 20, y - 10); 
    line(x, y2, x - 20, y + 40); 
    arc(x2, y2 - 15, 270, 90, 15);
    line(x, y, x + 30, y);
    line(x, y2, x + 30, y2);
    
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill((x + x2) / 2, (y + y2) / 2, YELLOW);

    // Movement
    if (GetAsyncKeyState('W')) { y -= speed; y2 -= speed; }
    if (GetAsyncKeyState('A')) { x -= speed; x2 -= speed; }
    if (GetAsyncKeyState('S')) { y += speed; y2 += speed; }
    if (GetAsyncKeyState('D')) { x += speed; x2 += speed; }

    // Screen boundaries
    if (x < 0) { x = 0; x2 = 50; }
    if (x2 > 1000) { x = 950; x2 = 1000; }
    if (y < 0) { y = 0; y2 = 30; }
    if (y2 > 630) { y = 600; y2 = 630; }
}

void bombb(Bomb &b) {
    if (!b.active) return;

    float rad = b.angle * M_PI / 180.0;
    int dx = cos(rad) * 10;
    int dy = sin(rad) * 10;

    b.x -= dx;
    b.y += dy;

    setcolor(RED);
    circle(b.x, b.y, 15);
    setfillstyle(SOLID_FILL, RED);
    floodfill(b.x, b.y, RED);

    if (b.x < 0 || b.y > 640) {
        b.active = false;
    }
}

bool isgameover(int ran) {
    int bombradius = 15;
    for (int i = 0; i < ran; i++) {
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
                distancebetween(x2 + 15, y2 - 15, bombs[i]),
                distancebetween(x + 30, y, bombs[i]),
                distancebetween(x + 30, y2, bombs[i])
            };

            for (int j = 0; j < 13; j++) {
                if (distances[j] <= bombradius) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    srand(time(0));
    initwindow(1920, 640, "kynm windows");

    bool spawnbomb = true;
    int ran = 5;

    while (true) {
        cleardevice();
        setbkcolor(LIGHTBLUE);

        // Bomb spawning logic
        if (spawnbomb) {
            ran = (rand() % 6) + 1;  
            for (int i = 0; i < ran; i++) {
                bombs[i].x = 1900;
                bombs[i].y = (rand() % (630 - 50)) + 25;
                bombs[i].angle = rand() % 360;
                bombs[i].active = true;
            }
            spawnbomb = false;
        }

        // Bomb movement
        bool allInactive = true;
        for (int i = 0; i < ran; i++) {
            if (bombs[i].active) {
                bombb(bombs[i]);
                allInactive = false;
            }
        }
        if (allInactive) spawnbomb = true;

        // Player movement
        player();

        // Check for game over
        if (isgameover(ran)) {
            outtextxy(500, 300, "GAME OVER!");
            break;
        }

        // Exit game
        if (GetAsyncKeyState(VK_RETURN)) {
            break;
        }

        delay(20);
    }

    getch();
    closegraph();
    return 0;
}
