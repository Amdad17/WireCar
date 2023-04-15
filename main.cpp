#include <windows.h>
#include <time.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include <fstream>
#include <iostream>
#define GLUT_DISABLE_ATEXIT_HACK // In case of errors like undefined reference to `__glutInitWithExit@12’, should be before including glut.h 
#define PI 3.14159265

int screenWidth = 600;
int screenHeight = 600;
int delay = 20;
double alfa = 0;
int    fx = 0, fy = 0, fz = 0;
float  sphi = 0.0, stheta = 0.0;
float  sside = 0, sdepth = -5;
float  sx = 0, sy = 0;
bool  mouse_left_click, mouse_middle_click, mouse_right_click;
int   mouseX, mouseY;

// --------------------------------- Cube ------------------------------------
double cube_flt[3] = { 4, 0, 0 };
double cube_frt[3] = { 0, 4, 0 };
double cube_frb[3] = { -4, 0, 0 };
double cube_flb[3] = { 0, -4, 0 };
double cube_blt[3] = { 4, 0, 2 };
double cube_brt[3] = { 0, 4, 2 };
double cube_brb[3] = { -4, 0, 2 };
double cube_blb[3] = { 0, -4, 2 };

// ------------------------------- Axles ----------------------------------
double axles_fl[3] = { 5 , -1, 2.1 };
double axles_fr[3] = { -1, 5 , 2.1 };
double axles_bl[3] = { 1, -5 , 2.1 };
double axles_br[3] = { -5, 1, 2.1 };

// -------------------------- Steering Column -----------------------------
double sc_b[3] = { 2 , 2 ,  2.1 };
double sc_t[3] = { 2 , 2 , -3.1 };

// -------------------------- Steering Wheel ------------------------------
double sw_l[3] = { 3 , 2 , -3.1 };
double sw_r[3] = { 1 , 2 , -3.1 };
double sw_b[3] = { 2, 1, -3.1 };
double sw_t[3] = { 2, 3 , -3.1 };

// ----------------------------- Tires ------------------------------------
double t_fl_1[3] = { 0,0,0 };
double t_fl_2[3] = { 0,0,0 };
double t_fl_11[3] = { 0,0,0 };
double t_fl_22[3] = { 0,0,0 };
double t_fr_1[3] = { 0,0,0 };
double t_fr_2[3] = { 0,0,0 };
double t_fr_11[3] = { 0,0,0 };
double t_fr_22[3] = { 0,0,0 };
double t_bl_1[3] = { 0,0,0 };
double t_bl_2[3] = { 0,0,0 };
double t_bl_11[3] = { 0,0,0 };
double t_bl_22[3] = { 0,0,0 };
double t_br_1[3] = { 0,0,0 };
double t_br_2[3] = { 0,0,0 };
double t_br_11[3] = { 0,0,0 };
double t_br_22[3] = { 0,0,0 };

// -------------------------- radius ------------------------------------
double r = 1;

// -------------------------- theta and tangle  --------------------------
double theta = 0;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< myIdle >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//   Animation routine which calls itself after “delay” miliseconds.
void myIdle(int frame)
{
    alfa += 10;
    if (alfa > 360) alfa -= 360;

    // ------------------------------------------  tire_front-left  ----------------------------------------------------------------------

    t_fl_1[0] = 5;
    t_fl_1[1] = -1 + cos(alfa * PI / 180);
    t_fl_1[2] = 2.1 + sin(alfa * PI / 180);

    t_fl_2[0] = 5;
    t_fl_2[1] = -1 + cos((alfa + 180) * PI / 180);
    t_fl_2[2] = 2.1 + sin((alfa + 180) * PI / 180);


    t_fl_11[0] = 5 + (t_fl_1[0] - 5) * cos((theta - 45) * PI / 180) - (t_fl_1[1] - (-1)) * sin((theta - 45) * PI / 180);
    t_fl_11[1] = (-1) + (t_fl_1[0] - 5) * sin((theta - 45) * PI / 180) + (t_fl_1[1] - (-1)) * cos((theta - 45) * PI / 180);
    t_fl_11[2] = t_fl_1[2];

    t_fl_22[0] = 5 + (t_fl_2[0] - 5) * cos((theta - 45) * PI / 180) - (t_fl_2[1] - (-1)) * sin((theta - 45) * PI / 180);
    t_fl_22[1] = (-1) + (t_fl_2[0] - 5) * sin((theta - 45) * PI / 180) + (t_fl_2[1] - (-1)) * cos((theta - 45) * PI / 180);
    t_fl_22[2] = t_fl_2[2];



    // ------------------------------------------  tire_front-right  ----------------------------------------------------------------------

    t_fr_1[0] = -1;
    t_fr_1[1] = 5 + cos(alfa * PI / 180);
    t_fr_1[2] = 2.1 + sin(alfa * PI / 180);

    t_fr_2[0] = -1;
    t_fr_2[1] = 5 + cos((alfa + 180) * PI / 180);
    t_fr_2[2] = 2.1 + sin((alfa + 180) * PI / 180);


    t_fr_11[0] = (-1) + (t_fr_1[0] - (-1)) * cos((theta - 45) * PI / 180) - (t_fr_1[1] - (5)) * sin((theta - 45) * PI / 180);
    t_fr_11[1] = (5) + (t_fr_1[0] - (-1)) * sin((theta - 45) * PI / 180) + (t_fr_1[1] - (5)) * cos((theta - 45) * PI / 180);
    t_fr_11[2] = t_fr_1[2];

    t_fr_22[0] = (-1) + (t_fr_2[0] - (-1)) * cos((theta - 45) * PI / 180) - (t_fr_2[1] - (5)) * sin((theta - 45) * PI / 180);
    t_fr_22[1] = (5) + (t_fr_2[0] - (-1)) * sin((theta - 45) * PI / 180) + (t_fr_2[1] - (5)) * cos((theta - 45) * PI / 180);
    t_fr_22[2] = t_fr_2[2];



    // ------------------------------------------  tire_back-left  -------------------------------------------------------------------------

    t_bl_1[0] = 1;
    t_bl_1[1] = -5 + cos(alfa * PI / 180);
    t_bl_1[2] = 2.1 + sin(alfa * PI / 180);

    t_bl_2[0] = 1;
    t_bl_2[1] = -5 + cos((alfa + 180) * PI / 180);
    t_bl_2[2] = 2.1 + sin((alfa + 180) * PI / 180);

    t_bl_11[0] = (1) + (t_bl_1[0] - (1)) * cos((-45) * PI / 180) - (t_bl_1[1] - (-5)) * sin((-45) * PI / 180);
    t_bl_11[1] = (-5) + (t_bl_1[0] - (1)) * sin((-45) * PI / 180) + (t_bl_1[1] - (-5)) * cos((-45) * PI / 180);
    t_bl_11[2] = t_bl_1[2];

    t_bl_22[0] = (1) + (t_bl_2[0] - (1)) * cos((-45) * PI / 180) - (t_bl_2[1] - (-5)) * sin((-45) * PI / 180);
    t_bl_22[1] = (-5) + (t_bl_2[0] - (1)) * sin((-45) * PI / 180) + (t_bl_2[1] - (-5)) * cos((-45) * PI / 180);
    t_bl_22[2] = t_bl_2[2];



    // -------------------------------------------  tire_back-right  ------------------------------------------------------------------------

    t_br_1[0] = -5;
    t_br_1[1] = 1 + cos(alfa * PI / 180);
    t_br_1[2] = 2.1 + sin(alfa * PI / 180);

    t_br_2[0] = -5;
    t_br_2[1] = 1 + cos((alfa + 180) * PI / 180);
    t_br_2[2] = 2.1 + sin((alfa + 180) * PI / 180);

    t_br_11[0] = (-5) + (t_br_1[0] - (-5)) * cos((-45) * PI / 180) - (t_br_1[1] - (1)) * sin((-45) * PI / 180);
    t_br_11[1] = (1) + (t_br_1[0] - (-5)) * sin((-45) * PI / 180) + (t_br_1[1] - (1)) * cos((-45) * PI / 180);
    t_br_11[2] = t_br_1[2];

    t_br_22[0] = (-5) + (t_br_2[0] - (-5)) * cos((-45) * PI / 180) - (t_br_2[1] - (1)) * sin((-45) * PI / 180);
    t_br_22[1] = (1) + (t_br_2[0] - (-5)) * sin((-45) * PI / 180) + (t_br_2[1] - (1)) * cos((-45) * PI / 180);
    t_br_22[2] = t_br_2[2];


    // Calling Itself
    glutTimerFunc(delay, myIdle, 0);
    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  circle drawing function for front tires >>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawCircleForFrontTires(double* center)
{
    int num_segments = 20;
    // center points
    double cx = center[0];
    double cy = center[1];
    double cz = center[2];
    float tbeta = 2 * PI / float(num_segments);
    float c = cosf(tbeta);
    float s = sinf(tbeta);
    float t;

    float x = r;
    float y = 0;
    double array_x[21];
    double array_y[21];
    double array_z[21];

    for (int ii = 0; ii < num_segments; ii++)
    {
        array_x[ii] = x + cx;
        array_y[ii] = x + cy;
        array_z[ii] = y + cz;

        t = x;
        x = x * c - y * s;
        y = t * s + y * c;
    }
    // draw the circle using gl_lines
    glBegin(GL_LINES);

    double vektor1[3] = { 0,0,0 };
    double vektor2[3] = { 0,0,0 };

    // draw the circle using arrays
    for (int j = 0; j < 20; j++)
    {


        if (j == 19) {

            vektor1[0] = cx + (array_x[19] - cx) * cos(theta * PI / 180) - (array_y[19] - cy) * sin(theta * PI / 180);
            vektor1[1] = cy + (array_x[19] - cx) * sin(theta * PI / 180) + (array_y[19] - cy) * cos(theta * PI / 180);
            vektor1[2] = array_z[19];

            vektor2[0] = cx + (array_x[0] - cx) * cos(theta * PI / 180) - (array_y[0] - cy) * sin(theta * PI / 180);
            vektor2[1] = cy + (array_x[0] - cx) * sin(theta * PI / 180) + (array_y[0] - cy) * cos(theta * PI / 180);
            vektor2[2] = array_z[0];


            glVertex3dv(vektor1);
            glVertex3dv(vektor2);
        }
        else {

            vektor1[0] = cx + (array_x[j] - cx) * cos(theta * PI / 180) - (array_y[j] - cy) * sin(theta * PI / 180);
            vektor1[1] = cy + (array_x[j] - cx) * sin(theta * PI / 180) + (array_y[j] - cy) * cos(theta * PI / 180);
            vektor1[2] = array_z[j];

            vektor2[0] = cx + (array_x[j + 1] - cx) * cos(theta * PI / 180) - (array_y[j + 1] - cy) * sin(theta * PI / 180);
            vektor2[1] = cy + (array_x[j + 1] - cx) * sin(theta * PI / 180) + (array_y[j + 1] - cy) * cos(theta * PI / 180);
            vektor2[2] = array_z[j + 1];

            glVertex3dv(vektor1);
            glVertex3dv(vektor2);
        }
    }
    glEnd();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< circle drawing function for back tires >>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawCircleForBackTires(double* center)
{
    int num_segments = 20;

    double cx = center[0];
    double cy = center[1];
    double cz = center[2];
    float tbeta = 2 * PI / float(num_segments);
    float c = cosf(tbeta);
    float s = sinf(tbeta);
    float t;

    float x = r;
    float y = 0;
    double array_x[21];
    double array_y[21];
    double array_z[21];


    for (int ii = 0; ii < num_segments; ii++)
    {
        array_x[ii] = x + cx;
        array_y[ii] = x + cy;
        array_z[ii] = y + cz;

        //apply the rotation matrix
        t = x;
        x = x * c - y * s;
        y = t * s + y * c;
    }

    // draw the circle using gl_lines
    glBegin(GL_LINES);

    double vektor1[3] = { 0,0,0 };
    double vektor2[3] = { 0,0,0 };

    // draw the circle using arrays
    for (int j = 0; j < 20; j++)
    {
        if (j == 19) {

            vektor1[0] = array_x[19];
            vektor1[1] = array_y[19];
            vektor1[2] = array_z[19];

            vektor2[0] = array_x[0];
            vektor2[1] = array_y[0];
            vektor2[2] = array_z[0];

            glVertex3dv(vektor1);
            glVertex3dv(vektor2);

        }

        else {

            vektor1[0] = array_x[j];
            vektor1[1] = array_y[j];
            vektor1[2] = array_z[j];

            vektor2[0] = array_x[j + 1];
            vektor2[1] = array_y[j + 1];
            vektor2[2] = array_z[j + 1];

            glVertex3dv(vektor1);
            glVertex3dv(vektor2);

        }
    }
    glEnd();
}

double perpective[9] = { 0, -25, -18, 0, 0, 0, 0, 1, 0 };
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< myinit >>>>>>>>>>>>>>>>>>>>>>>>>>>
void myInit(double* perpective)
{
    glColor3f(0.0f, 0.0f, 0.0f);  // set color of stuff
    glShadeModel(GL_FLAT);	// or can be GL_SMOOTH

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(45.0f, 1.0, 1.0, 100.0);

    gluLookAt(perpective[0], perpective[1], perpective[2], perpective[3], perpective[4], perpective[5], perpective[6], perpective[7], perpective[8]);
    glMatrixMode(GL_MODELVIEW);

    // Start animation
    myIdle(0);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< tires lines drawing >>>>>>>>>>>>>>>>>>>>>>>>>>>
void tires_lines() {
    glVertex3dv(t_fl_11);
    glVertex3dv(t_fl_22);

    glVertex3dv(t_fr_11);
    glVertex3dv(t_fr_22);

    glVertex3dv(t_bl_11);
    glVertex3dv(t_bl_22);

    glVertex3dv(t_br_11);
    glVertex3dv(t_br_22);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< tires circle drawing and rotation >>>>>>>>>>>>>>>>>>>>>>>>>>>
void tires_circle() {

    double tire1[3] = { 5 , -1, 2.1 };
    double tire2[3] = { -1, 5, 2.1 };
    double tire3[3] = { 1, -5 , 2.1 };
    double tire4[3] = { -5, 1, 2.1 };


    DrawCircleForFrontTires(tire1);
    DrawCircleForFrontTires(tire2);

    DrawCircleForBackTires(tire3);
    DrawCircleForBackTires(tire4);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< steering wheel vertices for rotation and drawing >>>>>>>>>>>>>>>>>>>>>>>>>>>
void steering_wheel() {

    //steering wheel rotation
    sw_l[0] = 2 + (cos((theta - 45) * PI / 180));
    sw_l[1] = 2 + (sin((theta - 45) * PI / 180));

    sw_r[0] = 2 + (cos((theta + 135) * PI / 180));
    sw_r[1] = 2 + (sin((theta + 135) * PI / 180));

    sw_b[0] = 2 + (cos((theta - 135) * PI / 180));
    sw_b[1] = 2 + (sin((theta - 135) * PI / 180));

    sw_t[0] = 2 + (cos((theta + 45) * PI / 180));
    sw_t[1] = 2 + (sin((theta + 45) * PI / 180));


    glVertex3dv(sw_l);
    glVertex3dv(sw_r);

    glVertex3dv(sw_b);
    glVertex3dv(sw_t);

    // steering wheel circle drawing
    double x = 1;
    double y = 2;
    double inc = 0.05;

    for (int i = 1; i <= 40; i++) {

        if (i <= 20) {
            double c1[3] = { x ,y ,-3.1 };
            x = x + inc;
            if (x == 2) {
                y = 1;
            }
            else {
                y = (2 - sqrt(-pow(x, 2) + 4 * x - 3));
            }
            double c2[3] = { x ,y,-3.1 };

            glVertex3dv(c1);
            glVertex3dv(c2);
        }

        else {
            double c1[3] = { x,y ,-3.1 };
            x = x + inc;
            if (x == 3) {
                y = 2;
            }
            else {
                y = (2 - sqrt(-pow(x, 2) + 4 * x - 3));
            }
            double c2[3] = { x,y,-3.1 };

            glVertex3dv(c1);
            glVertex3dv(c2);
        }
    }

    for (int j = 1; j <= 40; j++) {

        if (j <= 20) {
            double c1[3] = { x,y,-3.1 };
            x = x - inc;
            if (x == 2) {
                y = 3;
            }
            else {
                y = (2 + sqrt(-pow(x, 2) + 4 * x - 3));
            }
            double c2[3] = { x,y ,-3.1 };

            glVertex3dv(c1);
            glVertex3dv(c2);
        }

        else {
            double c1[3] = { x,y,-3.1 };
            x = x - inc;
            if (x == 1) {
                y = 2;
            }
            else {
                y = (2 + sqrt(-pow(x, 2) + 4 * x - 3));
            }
            double c2[3] = { x ,y ,-3.1 };

            glVertex3dv(c1);
            glVertex3dv(c2);
        }
    }

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< steering column vertices for drawing >>>>>>>>>>>>>>>>>>>>>>>>>>>
void steering_column() {
    glVertex3dv(sc_b);
    glVertex3dv(sc_t);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< axles vertices for drawing >>>>>>>>>>>>>>>>>>>>>>>>>>>
void axles() {

    glVertex3dv(axles_fl);
    glVertex3dv(axles_fr);

    glVertex3dv(axles_bl);
    glVertex3dv(axles_br);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< cube vertices for drawing >>>>>>>>>>>>>>>>>>>>>>>>>>>
void cube() {

    glVertex3dv(cube_flt);
    glVertex3dv(cube_frt);
    glVertex3dv(cube_frt);
    glVertex3dv(cube_frb);
    glVertex3dv(cube_frb);
    glVertex3dv(cube_flb);
    glVertex3dv(cube_flb);
    glVertex3dv(cube_flt);

    glVertex3dv(cube_blt);
    glVertex3dv(cube_brt);
    glVertex3dv(cube_brt);
    glVertex3dv(cube_brb);
    glVertex3dv(cube_brb);
    glVertex3dv(cube_blb);
    glVertex3dv(cube_blb);
    glVertex3dv(cube_blt);

    glVertex3dv(cube_flt);
    glVertex3dv(cube_blt);
    glVertex3dv(cube_frt);
    glVertex3dv(cube_brt);
    glVertex3dv(cube_frb);
    glVertex3dv(cube_brb);
    glVertex3dv(cube_flb);
    glVertex3dv(cube_blb);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<< myReshape >>>>>>>>>>>>>>>>>>>
void myReshape(int width, int height)
{
    glViewport(0, 0, width, height); // update viewport
    //glOrtho(-width,width,-height,height,-1000,1000);
    glOrtho(-1, 1, -1, 1, -1, 1);

}

// Text
void drawText(const char *text, int lenght, int x, int y, int z) {

    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[200];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos3i(x, y, z);
    for (int i = 0; i < lenght; i++) {

        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);

}
//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear screen

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(sside, 0, -sdepth);
    glRotatef(-stheta, 1, 0, 0);
    glRotatef(sphi, 0, 1, 0);
    glTranslatef(sx, 0, -sy);

    glColor3f(1, 1, 1);

    glBegin(GL_LINES);

    // my functions for drawing
    tires_lines();
    cube();
    axles();
    steering_column();
    steering_wheel();

    glEnd();

    tires_circle();

    std::string text1;
    std::string text2;
    std::string text3;
    std::string text4;
    std::string text5;
    std::string text6;

    text1 = "Left arrow to Left view";
    text2 = "Right arrow to right view";
    text3 = "Up arrow to upper view";
    text4 = "Down arrow to bottom view";
    text5 = "Press A to turn left";
    text6 = "Press S to turn right";

    drawText(text1.data(), text1.size(), 50, 450, 0);
    drawText(text2.data(), text2.size(), 50, 470, 0);
    drawText(text3.data(), text3.size(), 50, 490, 0);
    drawText(text4.data(), text4.size(), 50, 510, 0);
    drawText(text5.data(), text5.size(), 50, 530, 0);
    drawText(text6.data(), text6.size(), 50, 550, 0);

    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay2 for arrows >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay2(void) {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear screen

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_LINES);

    // my functions for drawing
    tires_lines();
    cube();
    axles();
    steering_column();
    steering_wheel();

    glEnd();

    tires_circle();

    glutSwapBuffers();

}

/** myMouse()
 *
 * This event callback is executed whenever there is a mouse event
 */
void myMouse(int button, int state, int x, int y)
{
    mouseX = x; mouseY = y;
    mouse_left_click = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
    mouse_middle_click = ((button == GLUT_MIDDLE_BUTTON) &&
        (state == GLUT_DOWN));
    mouse_right_click = ((button == GLUT_RIGHT_BUTTON) &&
        (state == GLUT_DOWN));
    glutPostRedisplay();
}


/** myMouseMove
 *
 * This even callback is executed whenver the mouse is moved
 */
void myMouseMove(int x, int y) {
    // rotate
    if (mouse_left_click)
    {
        sphi += (float)(x - mouseX) / 4.0;
        stheta += (float)(mouseY - y) / 4.0;
        // if (stheta<0) stheta=0;
    }

    // scale
    if (mouse_middle_click)
    {
        sx += (float)(x - mouseX) * 50;
        sy += (float)(y - mouseY) * 50;
    }

    // scale
    if (mouse_right_click)
    {
        sside += (float)(x - mouseX) * 50;
        sdepth += (float)(y - mouseY) * 50;
    }
    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key) {

    case 27:  // Escape
        exit(-1);
    case 'a':
        theta -= 1;
        //tangle -= 0.12;

        break;
    case 's':
        theta += 1;
        //tangle += 0.12;

        break;

    case 'A':
        theta -= 1;
        //tangle -= 0.12;
        break;
    case 'S':
        theta += 1;
        //tangle += 0.12;
        break;

    }


    glutPostRedisplay();
}

// Arrow keys
void specialInput(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP:

        perpective[0] = 0;
        perpective[1] = 0;
        perpective[2] = -15;
        perpective[3] = 0;
        perpective[4] = 0;
        perpective[5] = 0;
        perpective[6] = 0;
        perpective[7] = 1;
        perpective[8] = 0;

        glutCreateWindow("Upper Window");
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowPosition(0, 0);
        glutKeyboardFunc(myKeyboard);
        glutReshapeFunc(myReshape);
        glutDisplayFunc(myDisplay2);
        //glutMouseFunc(myMouse);
        glutMotionFunc(myMouseMove);
        glutInitWindowSize(screenWidth, screenHeight);
        glutPositionWindow(800, 40);
        myInit(perpective);

        break;
    case GLUT_KEY_DOWN:
        perpective[0] = 0;
        perpective[1] = 0;
        perpective[2] = 20;
        perpective[3] = 0;
        perpective[4] = 0;
        perpective[5] = 0;
        perpective[6] = 0;
        perpective[7] = 1;
        perpective[8] = 0;


        glutCreateWindow("Bottom Window");
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowPosition(0, 0);
        glutKeyboardFunc(myKeyboard);
        glutReshapeFunc(myReshape);
        glutDisplayFunc(myDisplay2);
        //glutMouseFunc(myMouse);
        glutMotionFunc(myMouseMove);
        glutInitWindowSize(screenWidth, screenHeight);
        glutPositionWindow(800, 40);
        myInit(perpective);

        break;
    case GLUT_KEY_LEFT:
        perpective[0] = 20;
        perpective[1] = -20;
        perpective[2] = 0;
        perpective[3] = 0;
        perpective[4] = 0;
        perpective[5] = 0;
        perpective[6] = 0;
        perpective[7] = 0;
        perpective[8] = -1;


        glutCreateWindow("Left Window");
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowPosition(0, 0);
        glutKeyboardFunc(myKeyboard);
        glutReshapeFunc(myReshape);
        glutDisplayFunc(myDisplay2);
        //glutMouseFunc(myMouse);
        glutMotionFunc(myMouseMove);
        glutInitWindowSize(screenWidth, screenHeight);
        glutPositionWindow(800, 40);
        myInit(perpective);

        break;
    case GLUT_KEY_RIGHT:
        perpective[0] = -20;
        perpective[1] = 20;
        perpective[2] = 0;
        perpective[3] = 0;
        perpective[4] = 0;
        perpective[5] = 0;
        perpective[6] = 0;
        perpective[7] = 0;
        perpective[8] = -1;


        glutCreateWindow("Right Window");
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowPosition(0, 0);
        glutKeyboardFunc(myKeyboard);
        glutReshapeFunc(myReshape);
        glutDisplayFunc(myDisplay2);
        //glutMouseFunc(myMouse);
        glutMotionFunc(myMouseMove);
        glutInitWindowSize(screenWidth, screenHeight);
        glutPositionWindow(800, 40);
        myInit(perpective);

        break;
    }

    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("WireCar");
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMouseMove);
    glutPositionWindow(100, 40);

    glutSpecialFunc(specialInput);

    myInit(perpective);


    glutMainLoop();
}