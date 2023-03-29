
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  20 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

#define RIGHT 1
#define LEFT 2

#define MENU 0
#define START 1
#define CONTROLS 2

#define cl 7



int state = MENU;
int direction = RIGHT;

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int rX = -290, rY = -80;
bool activeTimer = false;
int cli = 0;


//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void brickLines()
{
    glClearColor(1.0f, 0.25f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
    glLineWidth(4.00);

    glBegin(GL_LINES);

    // Horizontal Brick Lines
    glVertex2f(-winWidth / 2, 250);
    glVertex2f(winWidth / 2, 250);

    glVertex2f(-winWidth / 2, 200);
    glVertex2f(winWidth / 2, 200);

    glVertex2f(-winWidth / 2, 150);
    glVertex2f(winWidth / 2, 150);

    glVertex2f(-winWidth / 2, 100);
    glVertex2f(winWidth / 2, 100);

    glVertex2f(-winWidth / 2, 50);
    glVertex2f(winWidth / 2, 50);

    glVertex2f(-winWidth / 2, 0);
    glVertex2f(winWidth / 2, 0);

    glVertex2f(-winWidth / 2, -50);
    glVertex2f(winWidth / 2, -50);

    glVertex2f(-winWidth / 2, -100);
    glVertex2f(winWidth / 2, -100);

    glVertex2f(-winWidth / 2, -150);
    glVertex2f(winWidth / 2, -150);

    glVertex2f(-winWidth / 2, -200);
    glVertex2f(winWidth / 2, -200);

    glVertex2f(-winWidth / 2, -250);
    glVertex2f(winWidth / 2, -250);

    //Vertical Brick lines

    glVertex2f(-350, winHeight / 2);
    glVertex2f(-350, 250);

    glVertex2f(-250, winHeight / 2);
    glVertex2f(-250, 250);

    glVertex2f(-150, winHeight / 2);
    glVertex2f(-150, 250);

    glVertex2f(-50, winHeight / 2);
    glVertex2f(-50, 250);

    glVertex2f(50, winHeight / 2);
    glVertex2f(50, 250);

    glVertex2f(150, winHeight / 2);
    glVertex2f(150, 250);

    glVertex2f(250, winHeight / 2);
    glVertex2f(250, 250);

    glVertex2f(350, winHeight / 2);
    glVertex2f(350, 250);

    
    glVertex2f(-300, 250);
    glVertex2f(-300, 200);

    glVertex2f(-200, 250);
    glVertex2f(-200, 200);

    glVertex2f(-100, 250);
    glVertex2f(-100, 200);

    glVertex2f(0, 250);
    glVertex2f(0, 200);

    glVertex2f(100, 250);
    glVertex2f(100, 200);

    glVertex2f(200, 250);
    glVertex2f(200, 200);

    glVertex2f(300, 250);
    glVertex2f(300, 200);

    glVertex2f(400, 250);
    glVertex2f(400, 200);

    
    glVertex2f(-300, -winHeight / 2);
    glVertex2f(-300, -250);

    glVertex2f(-200, -winHeight / 2);
    glVertex2f(-200, -250);

    glVertex2f(-100, -winHeight / 2);
    glVertex2f(-100, -250);

    glVertex2f(0, -winHeight / 2);
    glVertex2f(0, -250);

    glVertex2f(100, -winHeight / 2);
    glVertex2f(100, -250);

    glVertex2f(200, -winHeight / 2);
    glVertex2f(200, -250);

    glVertex2f(300, -winHeight / 2);
    glVertex2f(300, -250);

    glVertex2f(400, -winHeight / 2);
    glVertex2f(400, -250);

    //
    glVertex2f(-350, -250);
    glVertex2f(-350, -200);

    glVertex2f(-250, -250);
    glVertex2f(-250, -200);
    
    glVertex2f(-150, -250);
    glVertex2f(-150, -200);

    glVertex2f(50, -250);
    glVertex2f(50, 200);

    glVertex2f(-50, -250);
    glVertex2f(-50, 200);

    glVertex2f(150, -250);
    glVertex2f(150, -200);

    glVertex2f(250, -250);
    glVertex2f(250, -200);

    glVertex2f(350, -250);
    glVertex2f(350, -200);
    
    glVertex2f(450, -250);
    glVertex2f(450, -200);


    glEnd();
}

void windowDisplay()
{
    glColor3ub(139, 69, 19);
    glRectf(-300, 200, 300, 190);
    
    glRectf(-300, -200, 300, -190);

    glRectf(-300, 200, -290, -200);

    glRectf(300, 200, 290, -200);

    
    
}


// The initial Color Of the car
int r = 25, g = 25, b = 112;

void displayCar(int x, int y)
{
    glColor3ub(r, g, b);
    glRectf(x, y, x + 120, y - 30);
    glRectf(x + 20, y, x + 100, y + 25);

    glColor3f(1, 1, 1);
    glRectf(x + 70, y + 5, x + 90, y + 20);

    glColor3ub(255, 45, 123);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 30, y + 5);
    glVertex2f(x + 40 , y + 20);
    glVertex2f(x + 50, y + 5);
    glEnd();

    glColor3ub(245, 237, 3);
    circle(x + 115, y - 5, 5);

    glColor3f(0, 0, 0);
    circle(x + 20, y - 30, 10);
    circle(x + 100, y - 30, 10);


    glColor3f(0.2, 0.2, 0.2);
    circle(x + 20, y - 30, 6);
    circle(x + 100, y - 30, 6);

    glColor3ub(245, 237, 3);
    glBegin(GL_POLYGON);
    glVertex2f(x + 10 , y - 2);
    glVertex2f(x + 5, y - 5);
    glVertex2f(x + 5, y - 10);
    glVertex2f(x + 10, y - 13);
    glVertex2f(x + 15, y - 10);
    glVertex2f(x + 15, y - 5);
    glEnd();
}


void drawBackgroundSky(int x, int y)
{
    glColor3f(1, 1, 1);
    circle(x, y, 40);
    circle(x + 40, y - 20, 25);
    circle(x - 45, y - 10, 15);
}

void housesAndCity()
{
    glColor3ub(139, 115, 85);
    glRectf(-250, -80, -230, 30);

    glColor3ub(85, 107, 47);
    circle(-250, 20, 30);
    circle(-240, 40, 30);
    circle(-230, 20, 30);

    glColor3ub(255, 218, 185);
    glRectf(-100, -80, 50, 70);

    glColor3ub(139, 71, 38);
    glRectf(-20, -80, 20, -10);

    glColor3ub(205, 200, 177);
    glBegin(GL_TRIANGLES);
    glVertex2f(-100,70);
    glVertex2f(50, 70);
    glVertex2f(-25, 150);
    glEnd();

    glColor3ub(139, 69, 19);
    circle(-25, 100, 15);

    glColor3ub(255, 215, 0);
    circle(-25, 100, 10);

    glColor3ub(139, 69, 19);
    glRectf(-93, -43, -27, 3);

    glColor3ub(255, 215, 0);
    glRectf(-90, -40, -30, 0);

    glColor3ub(0, 0, 0);
    circle(10, -45, 5);

}

void windowPanes()
{
    glColor3ub(255, 248, 220);
    glRectf(-450, 200, -300, -200);
    glRectf(450, 200, 300, -200);
}

//
// To display onto window using OpenGL commands
//
int roadX = 0, roadX2 = 0;
int cloudX1 = 100, cloudX2 = -150;
void display() {
    //
    // clear window to black
    //
    
    glClearColor(0.2, 0.2, 0.2, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (state == START)
    {
        brickLines();

        glColor3f(0.1, 0.1, 0.1);
        glRectf(-290, -190, 290, -80);

        glColor3ub(255, 255, 51);
        glRectf(roadX2 - 150, -120, roadX2 - 50, -130);
        glRectf(roadX + 100, -120, roadX + 0, -130);

        glColor3ub(135, 206, 250);
        glRectf(-290, -80, 290, 190);

        drawBackgroundSky(cloudX1, 120);
        drawBackgroundSky(cloudX2, 130);

        housesAndCity();

        displayCar(rX, rY);
        
        if (rX > 300)
        {
            rX = -350;
        }
            
        if (rX < -350)
        {
            rX = 250;
        }
       
        windowDisplay();

        windowPanes();
        if (cli == cl)
        {
            glColor3ub(255, 255, 0);
            glRectf(-290, 190, 290, -190);
        }
        
        glColor3f(0, 0, 0);
        vprint(-360, 50, GLUT_BITMAP_HELVETICA_12, "The");
        vprint(-370, 30, GLUT_BITMAP_HELVETICA_12, "Window");
        vprint(-368, 10, GLUT_BITMAP_HELVETICA_12, "View");
        vprint(-360, -10, GLUT_BITMAP_HELVETICA_12, "BY");
        vprint(-380, -30, GLUT_BITMAP_HELVETICA_12, "Talal Salman");
        vprint(-370, -50, GLUT_BITMAP_HELVETICA_12, "Zafeer");\
        vprint(310, 0, GLUT_BITMAP_HELVETICA_12, "<F2> -> MENU"); \
    }
    else if (state == MENU)
    {
        glColor3f(1, 1, 1);
        vprint(-140, 50, GLUT_BITMAP_TIMES_ROMAN_24, "     \"The Street View\"");
        vprint(-130, 25, GLUT_BITMAP_HELVETICA_12, "                Press <1> to start");
        vprint(-125, 0, GLUT_BITMAP_HELVETICA_12, "       Press <F3> to see controls");
        vprint(-360, 250, GLUT_BITMAP_HELVETICA_12, "Talal Salman Zafeer 22001483");
    }
    else if (state == CONTROLS)
    {
        glColor3f(1, 1, 1);
        vprint(-250, 100, GLUT_BITMAP_HELVETICA_18, "<SpaceBar> - Start And Stop the Animation/Game");
        vprint(-250, 80, GLUT_BITMAP_HELVETICA_18, "<Arrows Left & Right>  - Change direction/move in that direction");
        vprint(-250, 60, GLUT_BITMAP_HELVETICA_18, "<Right click> - Changes the color of the car");
        vprint(-250, 40, GLUT_BITMAP_HELVETICA_18, "<Left click>  - Close the Window Span");
        vprint(-250, 20, GLUT_BITMAP_HELVETICA_18, "<F2>          - Go back to the menu");
        vprint(-360, 360, GLUT_BITMAP_HELVETICA_12, "Talal Salman Zafeer 22001483");
    }


    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    if (key == '1' && state == MENU)
        state = START;

    if (key == ' ')
    {
        activeTimer = !activeTimer;
    }


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = true;
        break;
    case GLUT_KEY_DOWN:
        down = true;
        break;
    case GLUT_KEY_LEFT:
        left = true;
        break;
    case GLUT_KEY_RIGHT:
        right = true;
        break;
    }

    if (key == GLUT_KEY_F2)
        state = MENU;
    else if (key == GLUT_KEY_F3 && state == MENU) // to give access to the controls only from the menu not from the game itself
        state = CONTROLS;
    else if (key == GLUT_KEY_RIGHT)
    {
       direction = RIGHT;
       if (activeTimer == false)
       { 
           rX += 5;
       }
    }
    else if (key == GLUT_KEY_LEFT)
    {
         direction = LEFT;
        if (activeTimer == false)
        {
          rX -= 5;
        }
    }
   

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = false;
        break;
    case GLUT_KEY_DOWN:
        down = false;
        break;
    case GLUT_KEY_LEFT:
        left = false;
        break;
    case GLUT_KEY_RIGHT:
        right = false;
        break;
    }
    
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.
    
    int x2 = x - winWidth / 2;
    int y2 = winHeight / 2 - y;
    srand(time(NULL));

    
    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && activeTimer == false) {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
    
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (activeTimer == false)
    {
        switch (direction)
        {
        case RIGHT:
            rX++;
            //roadX--;
            //roadX2--;
            break;
        case LEFT:
            rX--;
            //roadX++;
            //roadX2++;
            break;
        }
        cloudX1 -= 2;
        cloudX2 -= 2;

        if (cloudX2 >= 380)
        {
            cloudX2 = -380;
        }

        if (cloudX2 <= -380)
        {
            cloudX2 = 380;
        }

        if(cloudX1 == -380)
            cloudX1 = -380;

        if (cloudX1 <= -380)
            cloudX1 = 380;


    }
    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Template File");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}