/*
PROBLEMS :
    1.Cannot prevent objects to be at the same location.
    ----------
    ADDITIONAL FEATURES :
    1. If ENTER button is pressed balloon's color will change.
    2. If clicks are tried to pressed more than 10 times there will be a message on the console (output screen).
    3. "-Press F1 to start/stop animation-" message apears on the window.
    4. If SPACEBAR is pressed objects will move vertically instead of horizontally and pressed once again it will continue horizontally.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  1000 // Period for the timer.
#define TIMER_ON        1// 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
bool activeTimer = false;
int  winWidth, winHeight; // current Window width and height


int x1 = 0, y2 = -55;
int xa = 0, ya = 0;
int xb = 0, yb = -55;
int radiusB = 75;
int r = 180, g = 172, b = 50;
int i = 0, j = 0;
int widthR = 100, heightR = 50;
int r1 = 255, g1 = 153, b1 = 9;
int cnt = 0;
float X[10];
float Y[10];
int nums[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
bool mode = true;

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



void onClick(int button, int stat, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN)
    {

        if (cnt == 10)
            printf("-You cannot display more than 10 objects-\n");

        if (cnt != 10)
        {
            cnt++;
            X[j] = x - winWidth / 2;
            Y[j] = winHeight / 2 - y;
            j++;
        }
        
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void background() {

    

    glColor3ub(92, 217, 255); //sky
    glRectf(winWidth / 2 , winHeight / 2 , -(winWidth / 2), winHeight / 2 - 300 );
    
    glColor3ub(207, 156, 6); //student info
    glRectf(-105, winHeight / 2 - 30, 25, winHeight / 2 - 80);

    glColor3ub(158, 74, 0); //tree body
    glRectf(winWidth / 2 - 230, winHeight / 2 - 450, winWidth / 2 - 190, winHeight / 2 - 550);
    glRectf(winWidth / 2 - 520, winHeight / 2 - 200, winWidth / 2 - 480, winHeight / 2 - 300);

    glColor3ub(23, 117, 11);  //tree leafs
    circle(winWidth / 2 - 220, winHeight / 2 - 420, 29);
    circle(winWidth / 2 - 200, winHeight / 2 - 460, 30);
    circle(winWidth / 2 - 200, winHeight / 2 - 450, 29);
    circle(winWidth / 2 - 190, winHeight / 2 - 440, 30);
    circle(winWidth / 2 - 230, winHeight / 2 - 460, 34);

    circle(winWidth / 2 - 510, winHeight / 2 - 190, 29);
    circle(winWidth / 2 - 490, winHeight / 2 - 230, 30);
    circle(winWidth / 2 - 490, winHeight / 2 - 220, 29);
    circle(winWidth / 2 - 480, winHeight / 2 - 210, 30);
    circle(winWidth / 2 - 520, winHeight / 2 - 230, 34);

    glColor3ub(135, 135, 135);  // Mountain body
    glBegin(GL_TRIANGLES);
    glVertex2f(-(winWidth / 2) + 200, winHeight/2 - 50);
    glVertex2f(-(winWidth / 2) + 80, winHeight / 2 - 300);
    glVertex2f(-(winWidth / 2) + 320, winHeight / 2 - 300);
    glEnd();

    glColor3ub(255, 255, 255);  // Mountain snow part
    glBegin(GL_TRIANGLES);
    glVertex2f(-(winWidth / 2) + 200, winHeight / 2 - 50);
    glVertex2f(-(winWidth / 2) + 177, winHeight / 2 - 100);
    glVertex2f(-(winWidth / 2) + 224, winHeight / 2 - 100);
    glEnd();

    glColor3ub(255, 247, 0);   //sun
    circle(-(winWidth/2) + 400, winHeight / 2 -100, 40);

}

void HotAirBalloon(int i) {



    glLineWidth(6);
    glColor3f(2, 1, 0);
    glBegin(GL_LINES);             // ropes of the balloon
    glVertex2f(X[i] - 30, Y[i] - radiusB + 30);
    glVertex2f(X[i] - 30, Y[i] - radiusB - radiusB * 0.8);
    glVertex2f(X[i] + 30, Y[i] - radiusB + 30);
    glVertex2f(X[i] + 30, Y[i] - radiusB - radiusB * 0.8);
    glEnd();
    glLineWidth(1);

    glColor3ub(r1, g1, b1);   //hot air balloon's balloon part
    circle(X[i], Y[i], radiusB);


    glColor3ub(23, 220, 211);   //design of the balloon
    glRectf(X[i] - 70, Y[i] + 20, X[i] + 70, Y[i] - 20);
    glColor3ub(23, 220, 211);
    glRectf(X[i] - 20, Y[i] + 70, X[i] + 20, Y[i] - 70);
    glColor3f(0, 0.6, 0.6);
    glRectf(X[i] - 20, Y[i] + 20, X[i] + 20, Y[i] - 20);
    glRectf(X[i] - 20, Y[i] + 20, X[i] + 20, Y[i] - 20);

    glLineWidth(6);    //ropes of the balloon
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(X[i] - 20, Y[i] + 20);
    glVertex2f(X[i] + 20, Y[i] - 20);
    glVertex2f(X[i] + 20, Y[i] + 20);
    glVertex2f(X[i] - 20, Y[i] - 20);
    glEnd();

    glColor3f(0, 0, 0);    // balloon's basket
    glRectf(X[i] - widthR / 2 - 2, Y[i] - heightR / 2 - 132, X[i] + widthR / 2 + 2, Y[i] + heightR / 2 - 128);
    glColor3ub(99, 69, 155);
    glRectf(X[i] - widthR / 2, Y[i] - heightR / 2 - 130, X[i] + widthR / 2, Y[i] + heightR / 2 - 130);
    glColor3ub(77, 95, 171);
    glRectf(X[i] - widthR / 2, Y[i] - heightR / 3 - 130, X[i] + widthR / 2, Y[i] + heightR / 3 - 130);
    glColor3f(0, 1, 1);
    vprint(X[i] - widthR / 2 + 44, Y[i] - heightR / 3 - 120, GLUT_BITMAP_8_BY_13, "%d", nums[i]);           // displaying numbers of the balloons

}

void display() {


    glClearColor(0, 6, 0.4, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    background();
    glColor3f(1, 0, 0);
   
    glColor3ub(0, 145, 158);
    vprint(-95, winHeight / 2 - 50, GLUT_BITMAP_HELVETICA_18, "Mert Koroglu");
    vprint(-85, winHeight / 2 - 70, GLUT_BITMAP_HELVETICA_18, "22003433");
    

    for (i = 0; i < cnt; i++)
    {
        HotAirBalloon(i);

    }

    glColor3ub(0, 0, 0);
    vprint(-(winWidth / 2) + 20, -(winHeight / 2) + 40, GLUT_BITMAP_8_BY_13, "(x: %d y : %d)", xa, ya);  //cordinates of x and y
    vprint(-100, -(winHeight / 2) + 40, GLUT_BITMAP_8_BY_13, "-Press F1 to start/stop animation-");

    glutSwapBuffers();
}


void onKeyDown(unsigned char key, int x, int y)
{

    if (key == 27)                           // EXIT button exits the code
        exit(0);
    if (key == 13)                           // ENTER button to change the color randomly of the baloon
    {
        r1 = rand() % 256;
        g1 = rand() % 256;
        b1 = rand() % 256;
    }
    if (key == 32)                         // SPACEBAR to change animation vertically instead of horizontally
        mode = !mode;
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{

    if (key == 27)
        exit(0);


    glutPostRedisplay();
}


void onSpecialKeyDown(int key, int x, int y)
{

    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    
    if (key == GLUT_KEY_F1)
    {

        activeTimer = !activeTimer;              //F1 key to start and stop the animation

    }
    

    glutPostRedisplay();
}


void onSpecialKeyUp(int key, int x, int y)
{

    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }


    glutPostRedisplay();
}

void onMove(int x, int y) {

    xa = x - winWidth / 2;
    ya = winHeight / 2 - y;



    glutPostRedisplay();
}




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
    display();
}

void onMoveDown(int x, int y) {

    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(10, onTimer, 0);

    if (activeTimer)
    {
        if (mode == true)
        {
            for (int a = 0; a < j; a++)                                   // Horizontal movement.
            {
                if (X[a] == winWidth / 2 + radiusB)
                    X[a] = -winWidth / 2 - radiusB;
                X[a]++;
            }
        }
        else
            for (int a = 0; a < j; a++)                                   // Vertical movement.
            {
                if (Y[a] == winHeight / 2 + 160)
                    Y[a] = -winHeight / 2 - radiusB;
                Y[a]++;
            }
    }



    glutPostRedisplay();

}
#endif

void Init() {


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Mert Köroðlu 22003433");

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
