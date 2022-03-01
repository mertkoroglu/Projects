/*********
   
PROBLEMS:
1) Start and End circles are placed from beginning.
----------
ADDITIONAL FEATURES:
1) Space bar changes end circle's color randomly
2) Enter changes start circle's color randomly
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
#define TIMER_ON         0 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

#define  START 0
#define  END  1
#define  LINES   2

int state = START;
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

double xa, xb, ya, yb;
bool first = true;
int X[20];
int Y[20];
int j = 0;
int cnt = 0;
int i = 0;
double a, b, z, d, e, f, g;
double xi, yi;
int r1 = 94, r2 = 255, r3 = 0;
int e1 = 94, e2 = 255, e3 = 0;
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

void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN)
    {
        if (state == START)
        {
            xa = x - winWidth / 2;
            ya = winHeight / 2 - y;
        }
        else if (state == END)
        {
            xb = x - winWidth / 2;
            yb = winHeight / 2 - y;
        }
        else if (state == LINES)
        {
            if (cnt != 20)
            {
                cnt++;
                X[j] = x - winWidth / 2;
                Y[j] = winHeight / 2 - y;
                j++;
            }

        }
    }
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

int calculate(int t) {

    a = xb - xa;
    b = yb - ya;
    z = X[t] - xa;
    d = Y[t] - ya;
    e = X[t - 1] - X[t];
    f = Y[t - 1] - Y[t];

    xi = ((e * d) - (f * z)) / ((e * b) - (a * f));

    yi = ((a * d) - (z * b)) / ((e * b) - (a * f));

    if ((xi >= 0 && xi <= 1) && (yi >= 0 && yi <= 1))
    {
        return(1);
    }
    else
        return(0);
}

//
// To display onto window using OpenGL commands
//
void lines(int c) {

    glColor3ub(0, 0, 0);
    circle(X[c], Y[c], 10);



    if (c % 2 != 0)
    {
        if (calculate(c) == 1)
        {
            glColor3ub(255, 0, 0);
        }
        else
            glColor3ub(0, 255, 0);

        glBegin(GL_LINES);
        glVertex2f(X[c - 1], Y[c - 1]);
        glVertex2f(X[c], Y[c]);
        glEnd();

    }
}

void display() {
    //
    // clear window to black
    //
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    //Grid
    glBegin(GL_LINES);
    for (int a = 0; a < 50; a++)
    {
        glColor3ub(43, 179, 156);
        glVertex2f(-winWidth / 2, winHeight / 2 - a * 50);
        glVertex2f(winWidth / 2, winHeight / 2 - a * 50);
        glColor3ub(189, 166, 38);
        glVertex2f(-winWidth / 2 + a * 50, winHeight / 2);
        glVertex2f(-winWidth / 2 + a * 50, -winHeight / 2);
    }
    glEnd();

    //START/END LINE
    glColor3ub(0, 4, 166);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(xa, ya);
    glVertex2f(xb, yb);
    glEnd();

    glLineWidth(1);

    //START Circle
    glColor3ub(0, 0, 0);
    circle(xa, ya, 39);
    glColor3ub(r1, r2, r3);
    circle(xa, ya, 35);
    glColor3ub(0, 0, 255);
    vprint(xa - 5, ya - 5, GLUT_BITMAP_TIMES_ROMAN_24, "S");

    //END Circle
    glColor3ub(0, 0, 0);
    circle(xb, yb, 39);
    glColor3ub(e1, e2, e3);
    circle(xb, yb, 35);
    glColor3ub(0, 0, 255);
    vprint(xb - 5, yb - 5, GLUT_BITMAP_TIMES_ROMAN_24, "E");

    //display lines
    for (int c = 0; c < cnt; c++)
        lines(c);



    glColor3ub(0, 0, 92);
    glRectf(-winWidth / 2, -winHeight / 2, winWidth / 2, -winHeight / 2 + 30);
    glRectf(-winWidth / 2, winHeight / 2, winWidth / 2, winHeight / 2 - 30);

    glColor3ub(217, 99, 76);
   
    switch (state)
    {
    case START:
        circle(-winWidth / 2 + 19, -winHeight / 2 + 14, 15);
        break;
    case END:
        circle(-winWidth / 2 + 235, -winHeight / 2 + 14, 15);
        break;
    case LINES:
        circle(-winWidth / 2 + 435, -winHeight / 2 + 14, 15);
        break;
    }

    glColor3ub(255, 255, 255);
    vprint(-winWidth / 2 + 10, -winHeight / 2 + 12, GLUT_BITMAP_9_BY_15, "F1: Set Start Position  F2: Set End Position  F3: Add Lines");
    vprint(-winWidth / 2 + 10, winHeight / 2 - 24, GLUT_BITMAP_9_BY_15, "Mert KOROGLU - 22003433");
    glColor3ub(217, 90, 76);
    vprint(-winWidth / 2 + 700, winHeight / 2 - 24, GLUT_BITMAP_9_BY_15, "HW #2 - 2020-2021 Spring");



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
    if (key == 13)                           // changes start circle's color rondomly
    {
        r1 = rand() % 256;
        r2 = rand() % 256;
        r3 = rand() % 256;
    }
    if (key == 32)                         // changes end circles's color rondomly
    {
        e1 = rand() % 256;
        e2 = rand() % 256;
        e3 = rand() % 256;
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
    /*if (key == GLUT_KEY_F3)
        first = !first;*/

    if (key == GLUT_KEY_F1) {
        state = START;
    }

    else if (key == GLUT_KEY_F2) {
        state = END;
    }

    else if (key == GLUT_KEY_F3)
    {
        state = LINES;

    }



    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
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
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
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
