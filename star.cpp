#include <graphics.h>
#include <cmath>
#include <cstring>
#include <sstream>
#include <iomanip>

using namespace std;

// Function to draw a button
void drawButton(int x, int y, int width, int height, const char* text, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(x, y, x + width, y + height);
    setcolor(WHITE);
    rectangle(x, y, x + width, y + height);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(BLACK);
    outtextxy(x + (width - textwidth((char*)text)) / 2, y + (height - textheight((char*)text)) / 2, (char*)text);
}

// Function to check if a point is inside a rectangle
bool isInside(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight) {
    return (x >= rectX && x <= rectX + rectWidth && y >= rectY && y <= rectY + rectHeight);
}

// Function to draw the main menu
void drawMainMenu() {
    cleardevice();
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(150, 50, "Math Solver Program");
    
    // Draw buttons
    drawButton(150, 150, 300, 50, "1. Linear Equations", LIGHTBLUE);
    drawButton(150, 220, 300, 50, "2. Quadratic Equation", LIGHTGREEN);
    drawButton(150, 290, 300, 50, "3. Matrix Operations", LIGHTMAGENTA);
    drawButton(150, 360, 300, 50, "4. Exit", LIGHTRED);
}

// Function to draw the linear equations menu
void drawLinearMenu() {
    cleardevice();
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 50, "Linear Equations");
    
    drawButton(150, 150, 300, 50, "1. 3x3 System", LIGHTBLUE);
    drawButton(150, 220, 300, 50, "2. 2x2 System", LIGHTGREEN);
    drawButton(150, 290, 300, 50, "Back to Main Menu", LIGHTRED);
}

// Function to draw the matrix operations menu
void drawMatrixMenu() {
    cleardevice();
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 50, "Matrix Operations");
    
    drawButton(150, 100, 300, 40, "1. Addition/Subtraction", LIGHTBLUE);
    drawButton(150, 160, 300, 40, "2. Scalar/Multiplication", LIGHTGREEN);
    drawButton(150, 220, 300, 40, "3. Determinant", LIGHTMAGENTA);
    drawButton(150, 280, 300, 40, "4. Inverse", LIGHTCYAN);
    drawButton(150, 340, 300, 40, "Back to Main Menu", LIGHTRED);
}

// Function to draw the addition/subtraction menu
void drawAddSubMenu() {
    cleardevice();
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 50, "Matrix Addition/Subtraction");
    
    drawButton(150, 150, 300, 40, "1. Addition", LIGHTBLUE);
    drawButton(150, 210, 300, 40, "2. Subtraction", LIGHTGREEN);
    drawButton(150, 270, 300, 40, "Back to Matrix Menu", LIGHTRED);
}

// Function to draw the scalar/multiplication menu
void drawScalarMultMenu() {
    cleardevice();
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 50, "Matrix Scalar/Multiplication");
    
    drawButton(150, 150, 300, 40, "1. Scalar Multiplication", LIGHTBLUE);
    drawButton(150, 210, 300, 40, "2. Matrix Multiplication", LIGHTGREEN);
    drawButton(150, 270, 300, 40, "Back to Matrix Menu", LIGHTRED);
}

// Function to draw the determinant menu
void drawDeterminantMenu() {
    cleardevice();
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 50, "Matrix Determinant");
    
    drawButton(150, 150, 300, 40, "1. 3x3 Matrix", LIGHTBLUE);
    drawButton(150, 210, 300, 40, "2. 2x2 Matrix", LIGHTGREEN);
    drawButton(150, 270, 300, 40, "Back to Matrix Menu", LIGHTRED);
}

// Function to draw the inverse menu
void drawInverseMenu() {
    cleardevice();
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 50, "Matrix Inverse");
    
    drawButton(150, 150, 300, 40, "1. 3x3 Matrix", LIGHTBLUE);
    drawButton(150, 210, 300, 40, "2. 2x2 Matrix", LIGHTGREEN);
    drawButton(150, 270, 300, 40, "Back to Matrix Menu", LIGHTRED);
}

// Function to draw a back button
void drawBackButton() {
    drawButton(250, 350, 100, 40, "Back", LIGHTRED);
}

// Function to wait for back button click
void waitForBackButton() {
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            
            if (isInside(x, y, 250, 350, 100, 40)) {
                clearmouseclick(WM_LBUTTONDOWN);
                return;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
        delay(100);
    }
}

// Abstract base class
class Equation {
public:
    virtual void input() = 0;
    virtual void solve() = 0;
    virtual void drawSolution() = 0;
    virtual ~Equation() {}
};

// Linear equation class for 3 equations and 3 unknowns
class LinearEquation3 : public Equation {
private:
    double a, b, c, d, e, f, g, h, i, j, k, l;
    double x, y, z;
public:
    void input() override {
        cleardevice();
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(100, 50, "Linear Equation (3x3)");
        
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(100, 100, "Enter coefficients for the first equation (a, b, c, d):");
        a = getDoubleInput(100, 130);
        b = getDoubleInput(200, 130);
        c = getDoubleInput(300, 130);
        d = getDoubleInput(400, 130);
        
        outtextxy(100, 170, "Enter coefficients for the second equation (e, f, g, h):");
        e = getDoubleInput(100, 200);
        f = getDoubleInput(200, 200);
        g = getDoubleInput(300, 200);
        h = getDoubleInput(400, 200);
        
        outtextxy(100, 240, "Enter coefficients for the third equation (i, j, k, l):");
        i = getDoubleInput(100, 270);
        j = getDoubleInput(200, 270);
        k = getDoubleInput(300, 270);
        l = getDoubleInput(400, 270);
    }

    void solve() override {
        z = (((i*f)-(e*j))*((e*c)-(a*g))-((e*b)-(a*f))*((i*g)-(e*k)))/((((i*f)-(e*j))*((e*d)-(a*h)))-(((e*b)-(a*f))*((i*h)-(e*l))));
        y = (((e*d)-(a*h))-(((e*c)-(a*g))*z))/((e*b)-(a*f));
        x = (d - (c*z) - (b*y))/a;
    }
    
    void drawSolution() override {
        cleardevice();
        setcolor(YELLOW);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(100, 50, "Solution for Linear Equation (3x3)");
        
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        
        char buffer[100];
        sprintf(buffer, "x = %.2f", x);
        outtextxy(150, 150, buffer);
        
        sprintf(buffer, "y = %.2f", y);
        outtextxy(150, 200, buffer);
        
        sprintf(buffer, "z = %.2f", z);
        outtextxy(150, 250, buffer);
        
        drawBackButton();
        waitForBackButton();
    }
    
    static double getDoubleInput(int x, int y) {
        char input[20] = "";
        int i = 0;
        setcolor(WHITE);
        rectangle(x, y, x + 50, y + 20);
        
        while (true) {
            if (kbhit()) {
                char ch = getch();
                if (ch == 13) { // Enter key
                    break;
                } else if (ch == 8 && i > 0) { // Backspace
                    i--;
                    input[i] = '\0';
                } else if ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-') {
                    if (i < 19) {
                        input[i] = ch;
                        i++;
                        input[i] = '\0';
                    }
                }
                
                // Redraw input box
                setfillstyle(SOLID_FILL, BLACK);
                bar(x + 1, y + 1, x + 49, y + 19);
                outtextxy(x + 5, y + 5, input);
            }
        }
        
        return atof(input);
    }
};

class QuadraticEquation: public Equation {
private:
    double a, b, c;
    double x1, x2;
public:
    void input() override {
        cleardevice();
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(100, 50, "Quadratic Equation");
        
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(100, 120, "Enter coefficients (a, b, c):");
        a = LinearEquation3::getDoubleInput(100, 150);
        b = LinearEquation3::getDoubleInput(200, 150);
        c = LinearEquation3::getDoubleInput(300, 150);
    }

    void solve() override {
        double discriminant = pow(b, 2) - (4 * a * c);
        if (discriminant >= 0) {
            x1 = (-b + sqrt(discriminant)) / (2 * a);
            x2 = (-b - sqrt(discriminant)) / (2 * a);
        } else {
            // Handle complex roots
            x1 = x2 = 0;
        }
    }
    
    void drawSolution() override {
        cleardevice();
        setcolor(YELLOW);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(100, 50, "Solution for Quadratic Equation");
        
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        
        double discriminant = pow(b, 2) - (4 * a * c);
        if (discriminant >= 0) {
            char buffer[100];
            sprintf(buffer, "x1 = %.2f", x1);
            outtextxy(150, 150, buffer);
            
            sprintf(buffer, "x2 = %.2f", x2);
            outtextxy(150, 200, buffer);
        } else {
            outtextxy(150, 150, "Complex Roots:");
            
            double realPart = -b / (2 * a);
            double imaginaryPart = sqrt(-discriminant) / (2 * a);
            
            char buffer[100];
            sprintf(buffer, "x1 = %.2f + %.2fi", realPart, imaginaryPart);
            outtextxy(150, 200, buffer);
            
            sprintf(buffer, "x2 = %.2f - %.2fi", realPart, imaginaryPart);
            outtextxy(150, 250, buffer);
        }
        
        drawBackButton();
        waitForBackButton();
    }
};


int main() {
    // Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    // Enable mouse support
    registermousehandler(WM_LBUTTONDOWN, NULL);
    
    // Main program loop
    int currentScreen = 0; // 0 = main menu, 1 = linear, 2 = quadratic, 3 = matrix
    int subMenu = 0; // For sub-menus
    
    while (true) {
        if (currentScreen == 0) {
            drawMainMenu();
            
            // Wait for mouse click
            while (true) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    
                    if (isInside(x, y, 150, 150, 300, 50)) {
                        currentScreen = 1; // Linear equations
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 220, 300, 50)) {
                        QuadraticEquation qe;
                        qe.input();
                        qe.solve();
                        qe.drawSolution();
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 290, 300, 50)) {
                        currentScreen = 3; // Matrix operations
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 360, 300, 50)) {
                        closegraph();
                        return 0;
                    }
                    clearmouseclick(WM_LBUTTONDOWN);
                }
                delay(100);
            }
        } else if (currentScreen == 1) {
            drawLinearMenu();
            
            // Wait for mouse click
            while (true) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    
                    if (isInside(x, y, 150, 150, 300, 50)) {
                        LinearEquation3 le;
                        le.input();
                        le.solve();
                        le.drawSolution();
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 220, 300, 50)) {
                        // Implement 2x2 linear equation
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 290, 300, 50)) {
                        currentScreen = 0; // Back to main menu
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    }
                    clearmouseclick(WM_LBUTTONDOWN);
                }
                delay(100);
            }
        } else if (currentScreen == 3) {
            drawMatrixMenu();
            
            // Wait for mouse click
            while (true) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    int x, y;
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    
                    if (isInside(x, y, 150, 100, 300, 40)) {
                        subMenu = 1; // Addition/Subtraction
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 160, 300, 40)) {
                        subMenu = 2; // Scalar/Multiplication
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 220, 300, 40)) {
                        subMenu = 3; // Determinant
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 280, 300, 40)) {
                        subMenu = 4; // Inverse
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    } else if (isInside(x, y, 150, 340, 300, 40)) {
                        currentScreen = 0; // Back to main menu
                        clearmouseclick(WM_LBUTTONDOWN);
                        break;
                    }
                    clearmouseclick(WM_LBUTTONDOWN);
                }
                delay(100);
            }
            
            // Handle sub-menus
            if (subMenu == 1) {
                drawAddSubMenu();
                
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        
                        if (isInside(x, y, 150, 150, 300, 40)) {
                            // Implement matrix addition
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 210, 300, 40)) {
                            // Implement matrix subtraction
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 270, 300, 40)) {
                            subMenu = 0; // Back to matrix menu
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        }
                        clearmouseclick(WM_LBUTTONDOWN);
                    }
                    delay(100);
                }
            } else if (subMenu == 2) {
                drawScalarMultMenu();
                
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        
                        if (isInside(x, y, 150, 150, 300, 40)) {
                            // Implement scalar multiplication
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 210, 300, 40)) {
                            // Implement matrix multiplication
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 270, 300, 40)) {
                            subMenu = 0; // Back to matrix menu
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        }
                        clearmouseclick(WM_LBUTTONDOWN);
                    }
                    delay(100);
                }
            } else if (subMenu == 3) {
                drawDeterminantMenu();
                
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        
                        if (isInside(x, y, 150, 150, 300, 40)) {
                            // Implement 3x3 determinant
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 210, 300, 40)) {
                            // Implement 2x2 determinant
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 270, 300, 40)) {
                            subMenu = 0; // Back to matrix menu
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        }
                        clearmouseclick(WM_LBUTTONDOWN);
                    }
                    delay(100);
                }
            } else if (subMenu == 4) {
                drawInverseMenu();
                
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        
                        if (isInside(x, y, 150, 150, 300, 40)) {
                            // Implement 3x3 inverse
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 210, 300, 40)) {
                            // Implement 2x2 inverse
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        } else if (isInside(x, y, 150, 270, 300, 40)) {
                            subMenu = 0; // Back to matrix menu
                            clearmouseclick(WM_LBUTTONDOWN);
                            break;
                        }
                        clearmouseclick(WM_LBUTTONDOWN);
                    }
                    delay(100);
                }
            }
        }
    }
    
    closegraph();
    return 0;
}