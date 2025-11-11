#include <stdio.h>
#include <freeglut.h>
#include <stdlib.h>
#include "Sphere.h"
#include "Stars.h"
#include "Stars.c"

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

void updateCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0, 0, 0,
		0, 1, 0);
}
void myDisplay(void)
{
	updateCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (showStars)
	{
		drawStars();
	}

	glLoadIdentity();

	// set rotation for the sun
	glRotatef(theta * 10, 0.0, 1.0, 0.0);
	drawNormalizedSphere(sunColour, 20);
	glPushMatrix();// Save Suns matrix used for aligning planets on the suns rotation

		glRotatef(theta * 10, 0.0, 1.0, 0.0);
		glTranslatef(1.7, 0, 0); 
		glScalef(0.2, 0.2, 0.2);
		drawNormalizedSphere(planetColour1, 20);
		glPushMatrix();//Saves Planet matrix used for aligning moons on the planets rotation

			glRotatef(theta * 50, 0, 1.0, 0.0);
			glTranslatef(2, 0, 0);
			glScalef(0.1, 0.1, 0.1);
			drawNormalizedSphere(moonColour1,20); //Matrix of moon1 on planet 1

		glPopMatrix();

			glRotatef(theta * 30, 0, 1.0, 0);
			glTranslatef(2.5, 0, -2.5);
			glScalef(0.2, 0.2, 0.2);
			drawNormalizedSphere(moonColour2, 20);

		glPopMatrix();

		glPushMatrix();

			glRotatef(theta * 5, 0.0, 1.0, 0.0);
			glTranslatef(1, 0, -3);
			glScalef(0.5, 0.5, 0.5);
			drawNormalizedSphere(planetColour2, 20);

		glPopMatrix();
		
		glPushMatrix();

			glRotatef(theta * 10, 0.0, 1.0, 0.0);
			glTranslatef(2, 0, 5);
			glScalef(0.3, 0.3, 0.3);
			drawNormalizedSphere(planetColour3, 20);

		glPopMatrix();
		glPushMatrix();

			glRotatef(theta * 7, 0.0, 1.0, 0.0);
			glTranslatef(2, 0, -9);
			glScalef(0.4, 0.4, 0.4);
			drawNormalizedSphere(planetColour4, 20);

		glPopMatrix();
		glPushMatrix();

			glRotatef(theta * 20, 0.0, 1.0, 0.0);
			glTranslatef(0.5, 0, 1);
			glScalef(0.15, 0.15, 0.15);
			drawNormalizedSphere(planetColour5, 20);

		glPopMatrix();
		glPushMatrix();

			glRotatef(theta * 10, 0.0, 1.0, 0.0);
			glTranslatef(-4, 0, 3);
			glScalef(0.25, 0.25, 0.25);
			drawNormalizedSphere(planetColour6, 20);

		glPopMatrix();
		glPushMatrix();

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
		case 'w': //move forward
			camZ += moveSpeed;
			break;
		case 's': //move backward
			camZ -= moveSpeed;
			break;
		case 'a': //move right
			camX -= moveSpeed;
			break;
		case 'd': //move left
			camX += moveSpeed;
			break;
		case 'q': //move up
			camY += moveSpeed;
			break;
		case 'e': //move down
			camY -= moveSpeed;
			break;
		case 'r': //display lines
			showLines = !showLines;
			break;
		case 't': //display twinkling stars
			showStars = !showStars;
			break;
	}

	glutPostRedisplay();
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

	//initialize the rendering context
	initializeGL();
	// go into a perpetual loop
	glutMainLoop();
}