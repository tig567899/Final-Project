/**FINAL PROJECT
 * TIGER KONG 521784*/
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <ctime>
#include "Car.h"
#include "race.h"

#define AGAIN 1
#define QUIT 2

#define _USE_MATH_DEFINES

using namespace std;
/// Player controls
bool speed;
float angle = 0.0;
float lx= 0.0;
float lz= -1.0;
float x= -80.0, z = 0.0;
float deltangle = 0.0;
int xOrigin = -101;
/// Tools for counting laps
int laps = 0;
bool complete = true;
/// Tools for Time Trial Mode
bool timer = false;
time_t s;
time_t t;
/// Countdown tools
time_t a;
time_t c;
bool stop = true;
bool start = false;
/// Race Mode Tools
race* game;
int foes;
/// Game Mode
int mode;

/**
 * Creates a new "race" class object
 */
race* new_race(int opponents)
{
    race* round = new race(opponents);
    for (int x = 1; x <= opponents; x++)
    {
        int difficulty;
        cout << "You are racing to 3 laps." << endl;
        cout << "When game is loaded, press space to start." << endl;
        cout << "Please set the difficulty of opponent " << x << " (1-5)." << endl;
        cin >> difficulty;
        while (difficulty > 5 || difficulty < 1)
        {
            cout << "Please enter a valid number. (1-5)" << endl;
            cin >> difficulty;
        }
        car* vehicle = new car (difficulty, x);
        round->add_car(vehicle);
    }
    return round;
}

/**
 * Function controling mouse motions
 */
void mousemove(int x, int y)
{
    if (speed)
    {
        if (xOrigin >= -100)
        {
            deltangle = (x - xOrigin) * 0.01;
            lx = sin(angle + deltangle);
            lz = -cos(angle + deltangle);
        }
    }
}

/**
 *Initializing function
 */
void init3D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);
	glMatrixMode (GL_PROJECTION);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glOrtho(-100.0, 100, 0.0, 100, -100, 100);
}

/**
 * Function controlling Keyboard
 */
void Normkeys(unsigned char key, int xx, int yy)
{
    if (key == ' ')
    {
        a = time(NULL);
        start = true;
    }
    if (!stop)
    {
        if (key == 'w') // forward key
        {
            if (!timer)
            {
                timer = true;
                s = time(NULL);
                t = time(NULL);
            }
            if (abs(x+lx) >= 80 || abs(z+lz) >= 80)
            {
                if (abs(x+lx) <= 100 && abs(z+lz) <= 100)
                {
                    x += lx*1.66;
                    z += lz*1.66;
                    speed = true;
                    if ((x > -1 || x < 1) && z < 0 && !complete)
                    {
                        complete = true;
                        t = time(NULL);
                        laps++;
                    }
                    else if (z>1 && x >0)
                    {
                        complete = false;
                    }
                }
            }
        }
        else if (key == 's')
        {
            if (abs(x-lx) >= 80 || abs(z-lz) >= 80)
            {
                if (abs(x-lx) <= 100 && abs(z-lz) <= 100)
                {
                    x -= lx;
                    z -= lz;
                    speed = true;
                }
            }
        }
    }
    else if (key == 27)
    {
        exit(0);
    }
}

/**
 * Function controlling released keys
 */
void UpKeys(unsigned char key, int xx, int yy)
{
    if (key == 'w')
    {
        speed = false;
    }
    if (key == 's')
    {
        speed = false;
    }
}

/**
 * Function controlling mouse buttons
 */
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {

		if (state == GLUT_UP) {
            angle += deltangle;
			xOrigin = -101;
		}
		else
        {
			xOrigin = x;
		}
	}
}

/**
 * Resizing Function
 */
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

/**
 * Function displaying score on screen
 */
void displayscore(int x, int y, int z, int space_char, double scorevar)
{
    int j=0,p,k;
    GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

    p = scorevar;
    j = 0;
    k = 0;
    glColor3f(0.0, 0.0, 0.0);
    while(p > 9)
    {
        k = p % 10;
        glRasterPos3f ((x-(j*space_char)),y, z);
        glutBitmapCharacter(font_style1,48+k);
        j++;
        p /= 10;
    }
    glRasterPos3f ((x-(j*space_char)), y, z);
    glutBitmapCharacter(font_style1,48+p);
}

/**
 * Function creating graphics and shapes
 */
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex3f(-101.0, 0.0, 101.0);
        glVertex3f(-101.0, 0.0, -101.0);
        glVertex3f(101.0, 0.0, -101.0);
        glVertex3f(101.0, 0.0, 101.0); // floor

        /*Walls*/
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(89.0, 0.1, 89.0);
        glVertex3f(91.0, 0.1, 89.0);
        glVertex3f(91.0, 0.1, -89.0);
        glVertex3f(89.0, 0.1, -89.0);

        glVertex3f(89.0, 0.1, 89.0);
        glVertex3f(89.0, 0.1, 91.0);
        glVertex3f(-89.0, 0.1, 91.0);
        glVertex3f(-89.0, 0.1, 89.0);

        glVertex3f(-89.0, 0.1, -89.0);
        glVertex3f(-91.0, 0.1, -89.0);
        glVertex3f(-91.0, 0.1, 89.0);
        glVertex3f(-89.0, 0.1, 89.0);

        glVertex3f(-89.0, 0.1, -89.0);
        glVertex3f(-89.0, 0.1, -91.0);
        glVertex3f(89.0, 0.1, -91.0);
        glVertex3f(89.0, 0.1, -89.0);

        glColor3f(1.0, 0.5, 0.0);
        glVertex3f(-79.0, 0.1, 1.0);
        glVertex3f(-79.0, 0.1, -1.0);
        glVertex3f(-101.0, 0.1, -1.0);
        glVertex3f(-101.0, 0.1, 1.0);

        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-79.0, 0.0, -79.0);
        glVertex3f(-79.0, 20.0,-79.0);
        glVertex3f(79.0, 20.0, -79.0);
        glVertex3f(79.0, 0.0, -79.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(79.0, 0.0, -79.0);
        glVertex3f(79.0, 20.0, -79.0);
        glVertex3f(79.0, 20.0, 79.0);
        glVertex3f(79.0, 0.0, 79.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-79.0, 0.0, 79.0);
        glVertex3f(-79.0, 20.0, 79.0);
        glVertex3f(79.0, 20.0, 79.0);
        glVertex3f(79.0, 0.0, 79.0);

        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(-79.0, 0.0, -79.0);
        glVertex3f(-79.0, 20.0, -79.0);
        glVertex3f(-79.0, 20.0, 79.0);
        glVertex3f(-79.0, 0.0, 79.0);

    glEnd();

    if (mode == 1)
    {
        if (!stop)
        {
            for (int i = 0; i < foes; i++)
            {
                glBegin(GL_TRIANGLES);
                /* This is mainly for drawing the cars*/
                    glColor3f(1.0, 0.5, 0.0);
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                    ->return_angle()+0.46365),0.0,
                               game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                    ->return_angle()+0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                   ->return_angle()+3.14159-0.46365), 0.0,
                               game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                  ->return_angle()+3.14159-0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                   ->return_angle()+3.14159-0.46365), 0.75,
                               game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                  ->return_angle()+3.14159-0.46365));

                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                  ->return_angle()-0.46365), 0.0,
                               game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                  ->return_angle()-0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                  ->return_angle()-3.14159+0.46365), 0.0,
                               game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                  ->return_angle()-3.14159+0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                  ->return_angle()-3.14159+0.46365), 0.75,
                               game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                  ->return_angle()-3.14159+0.46365));
                glEnd();

                glBegin(GL_QUADS);
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                            ->return_angle()+0.46365),0.0,
                                       game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                            ->return_angle()+0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                           ->return_angle()+3.14159-0.46365),
                               0.75, game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                          ->return_angle()+3.14159-0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                          ->return_angle()-3.14159+0.46365), 0.75,
                                       game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                          ->return_angle()-3.14159+0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                          ->return_angle()-0.46365), 0.0,
                                       game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                          ->return_angle()-0.46365));

                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                           ->return_angle()+3.14159-0.46365), 0.0,
                                       game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                          ->return_angle()+3.14159-0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                           ->return_angle()+3.14159-0.46365),
                               0.75, game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                          ->return_angle()+3.14159-0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                          ->return_angle()-3.14159+0.46365), 0.75,
                                       game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                          ->return_angle()-3.14159+0.46365));
                    glVertex3f(game->return_quota()->at(i)->return_x()+sqrt(5)*sin(game->return_quota()->at(i)
                                                                                          ->return_angle()-3.14159+0.46365), 0.0,
                                       game->return_quota()->at(i)->return_z()-sqrt(5)*cos(game->return_quota()->at(i)
                                                                                          ->return_angle()-3.14159+0.46365));
                glEnd();

                game->return_quota()->at(i)->ai();
            }
        }
        //Constantly checks for winning status
        game->checkwin();
        if (laps == 3)
        {
            game->playerwin();
            stop = true; // freezes the game
            start = true;
        }
        if (game->return_win() == 0)
        {
            glColor3f(0.0, 0.0, 0.0);
            glRasterPos3f(-95, 6, -45);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"PLAYER WINS");
            glRasterPos3f(-101, 4, -45);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) "Press Esc to exit.");
        }
        else if (game->return_win() > 0 && game->return_win() <= foes)
        {
            glRasterPos3f(-95, 6, -45);
            displayscore(-101, 6, -45, 1, game->return_win());
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"CPU WINS");
            glRasterPos3f(-101, 4, -45);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) "Press Esc to exit.");
        }
    }
    while (stop && start) // countdown
    {
        c = time(NULL);
        while (c-a < 3)
        {
            c = time(NULL);
        }
        stop = false;
    }
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(-97, 10, -45);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"LAPS: "); // displays laps

    displayscore(-90, 10, -45, 1, laps);

    if (mode == 2)
    {
        glRasterPos3f(-101, 8, -45);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)"TIME(seconds): ");// Time for Time Trial Mode

        displayscore(-85, 8, -45, 1, t-s);
    }
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    cout << "What would you like to do?" << endl;
    cout << "1. Race" << endl;
    cout << "2. Time Trials" << endl;
    cout << "0. Exit" << endl;
    cin >> mode;
    while (mode < 0 || mode > 2)
    {
        cout << "That isn't a valid option." << endl;
        cout << "1. Race" << endl;
        cout << "2. Time Trials" << endl;
        cout << "0. Exit" << endl;
        cin >> mode;
    }
    if (mode == 0)
    {
        return 0;
    }
    else if (mode == 1)
    {
        cout << "How many opponents would you like to race against? (1-3)" << endl;
        cin >> foes;
        while (foes > 3 || foes <1)
        {
            cout << "Please enter a valid number. (1-3)" << endl;
            cin >> foes;
        }
        game = new_race(foes);
    }
    else if (mode == 2)
    {
        cout << "Press space to start." << endl;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(320,320);
    glutInitWindowPosition(100,100);
    glutCreateWindow("GLUT");
    init3D(1.0, 1.0, 1.0);

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutIdleFunc(renderScene);

    glutKeyboardFunc(Normkeys);
    glutKeyboardUpFunc(UpKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemove);

    glutMainLoop();
    return 0;
}
