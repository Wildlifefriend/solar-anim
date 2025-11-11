#include <stdio.h>
#include <freeglut.h>
#include <stdlib.h>
#include <math.h>
#include "Sphere.h"

// Camera Parameters
GLdouble camX = 0.0f, camY = 1.0f, camZ = 10.0f;
float moveSpeed = 0.2f;

char showLines = 1;
char showStars = 1;
double starCount = 500;

// angle of rotation
GLfloat theta = 0.0;

int windowWidth = 500;
int windowHeight = 500;

ColorBlend sunColour = { {1.0,1.0,0}, {1.0,0.5,0} };

ColorBlend planetColour1 = { {0.1,0.0,0.5}, {0.5,0.0,0.5} },
		   planetColour2 = { {0.0,0.75,0.0}, {0.0,0.75,0.0} },
		   planetColour3 = { {0.3,0.1,0.0},{0.4,0.2,0.0} },
		   planetColour4 = { {0.0,0.1,0.5},{0.0,0.2,0.7} },
		   planetColour5 = { {0.1,0.0,0.1},{0.0,0.1,0.3} },
		   planetColour6 = { {0.0,0.4,0.1},{0.0,0.2,0.5} },
		   planetColour7 = { {0.3,0.3,0.3},{0.0,0.2,0.2} };

ColorBlend moonColour1 = { {0.5,0.5,0.5},{0.4,0.4,0.4} },
		   moonColour2 = { {0.2,0.1,0.0},{0.3,0.2,0.0} },
		   moonColour3 = { {0.75,0.75,0.75},{0.0,0.0,0.7} };

typedef struct {
	float x, y, z;
} Vertex;

typedef struct {
	int v1, v2, v3;
} Face;

// When r is pressed it should showed the orbit paths of each planet
void drawOrbit(float radius)
{
	if (showLines)
	{
		drawOrbitRing(radius);
	}
}
// is called in my display to change where the user is looking if the user pressed the movement keys
void updateCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0, 0, 0,
		0, 1, 0);
}
// used to call everything that needs to be drawn, specifically the planets orbiting the sun
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	updateCamera();

	if (showStars)
	{
		glDisable(GL_DEPTH_TEST); //helps to draw all the stars behind
		drawStars();
		glEnable(GL_DEPTH_TEST); //allows depth to be drawn again
	}



	// set rotation for the sun
	glRotatef(theta * 10, 0.0, 1.0, 0.0);
	drawNormalizedSphere(sunColour, 20);
	glPushMatrix();// Save Suns matrix used for aligning planets on the suns rotation

		drawOrbit(1.7);
		glRotatef(theta * 10, 0.0, 1.0, 0.0);
		glTranslatef(1.7, 0, 0); 
		glScalef(0.2, 0.2, 0.2);
		drawNormalizedSphere(planetColour1, 20);
		glPushMatrix();//Saves Planet matrix used for aligning moons on the planets rotation
			
			drawOrbit(2);
			glRotatef(theta * 50, 0, 1.0, 0.0);
			glTranslatef(2, 0, 0);
			glScalef(0.1, 0.1, 0.1);
			drawNormalizedSphere(moonColour1,20); //Matrix of moon1 on planet 1

		glPopMatrix();

			drawOrbit(sqrt(pow(2.5,2)+ pow((-2.5),2)));
			glRotatef(theta * 30, 0, 1.0, 0);
			glTranslatef(2.5, 0, -2.5);
			glScalef(0.2, 0.2, 0.2);
			drawNormalizedSphere(moonColour2, 20);

		glPopMatrix();

		glPushMatrix();

			drawOrbit(sqrt(pow(7, 2) + pow((-3), 2)));
			glRotatef(theta * 5, 0.0, 1.0, 0.0);
			glTranslatef(7, 0, -3);
			glScalef(0.5, 0.5, 0.5);
			drawNormalizedSphere(planetColour2, 20);

		glPopMatrix();
		
		glPushMatrix();
			
			drawOrbit(sqrt(pow(2, 2) + pow((5), 2)));
			glRotatef(theta * 10, 0.0, 1.0, 0.0);
			glTranslatef(2, 0, 5);
			glScalef(0.3, 0.3, 0.3);
			drawNormalizedSphere(planetColour3, 20);

		glPopMatrix();
		glPushMatrix();
			
			drawOrbit(sqrt(pow(2, 2) + pow((-9), 2)));
			glRotatef(theta * 7, 0.0, 1.0, 0.0);
			glTranslatef(2, 0, -9);
			glScalef(0.4, 0.4, 0.4);
			drawNormalizedSphere(planetColour4, 20);

		glPopMatrix();
		glPushMatrix();

			drawOrbit(sqrt(pow(0.5, 2) + pow((1), 2)));
			glRotatef(theta * 20, 0.0, 1.0, 0.0);
			glTranslatef(0.5, 0, 1);
			glScalef(0.15, 0.15, 0.15);
			drawNormalizedSphere(planetColour5, 20);

		glPopMatrix();
		glPushMatrix();

			drawOrbit(sqrt(pow((-4), 2) + pow((3), 2)));
			glRotatef(theta * 10, 0.0, 1.0, 0.0);
			glTranslatef(-4, 0, 3);
			glScalef(0.25, 0.25, 0.25);
			drawNormalizedSphere(planetColour6, 20);

		glPopMatrix();
		glPushMatrix();

			drawOrbit(sqrt(pow(7, 2) + pow((-7), 2)));
			glRotatef(theta * 15, 0.0, 1.0, 0.0);
			glTranslatef(7, 0, -7);
			glScalef(0.7, 0.7, 0.7);
			drawNormalizedSphere(planetColour7, 20);

		glPopMatrix();



	glutSwapBuffers();
}

void myIdle()
{

	// update the rotation around the selected axis 
	theta += 0.01f;

	if (showStars)
	{
		updateStars();
	}
	// redraw the new state
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: //esc to exit
			exit(0);
		case 'r': //display lines
			showLines = !showLines;
			break;
		case 's': //display twinkling stars
			showStars = !showStars;
			break;
	}

	glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_PAGE_UP: //move forward
		camZ += moveSpeed ;
		break;
	case GLUT_KEY_PAGE_DOWN: //move backward
		camZ -= moveSpeed;
		break;
	case GLUT_KEY_RIGHT: //move right
		camX += moveSpeed;
		break;
	case GLUT_KEY_LEFT: //move left
		camX -= moveSpeed;
		break;
	case GLUT_KEY_UP: //move up
		camY += moveSpeed;
		break;
	case GLUT_KEY_DOWN: //move down
		camY -= moveSpeed;
		break;
	}
}

//Iniatizes all basic window requirements including the camera
void initializeGL(void)
{
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set background color to be black
	glClearColor(0, 0, 0, 1.0);

	// change into projection mode so that we can change the camera properties
	glMatrixMode(GL_PROJECTION);

	// load the identity matrix into the projection matrix
	glLoadIdentity();

	// set window mode to perspective camera
	gluPerspective(60.0, windowWidth / windowHeight, 0.1, 100);

	// set where and what the camera is looking at
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	// change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	initStars(); //need to pregenerate locations of the stars
}

//loops for every fram
void main(int argc, char** argv)
{
	// initialize the toolkit
	glutInit(&argc, argv);
	// set display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// set window size
	glutInitWindowSize(windowWidth, windowHeight);
	// set window position on screen
	glutInitWindowPosition(100, 150);
	// open the screen window
	glutCreateWindow("colorcube");

	// register redraw function
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);

	//initialize the rendering context
	initializeGL();
	// go into a perpetual loop
	glutMainLoop();
}