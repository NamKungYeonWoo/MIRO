// MIRO.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define WALK 0.05
#define TURN 0.02

int map[30][30] = { { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
{ 1,1,1,0,1,1,1,0,1,0,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1 },
{ 1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1 },
{ 1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1 },
{ 1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,1 },
{ 1,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1 },
{ 1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,1,1 },
{ 1,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,1,1 },
{ 1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1 },
{ 1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1 },
{ 1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,1,1,1,0,1,1,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,0,0,0,0,1,1 },
{ 1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1 },
{ 1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,1,1,1 },
{ 1,0,0,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1 },
{ 1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,0,0,0,1,1 },
{ 1,0,1,0,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,1,1 },
{ 1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1 },
{ 1,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1,0,1 },
{ 1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1 },
{ 1,0,1,0,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1 },
{ 1,0,1,0,1,1,1,0,1,0,1,0,0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,1 },
{ 1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1,1,1,0,1 },
{ 1,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1 },
{ 1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1 },
{ 1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,1 },
{ 1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1 } };

int width = 500, height = 500;

static boolean music = true, start = true;

static GLfloat theta = 0.0; // variable for rotation
static GLfloat scale = 0.7;
static int axis = 0;

static GLfloat eyeX = 2;
static GLfloat eyeY = 2;
static GLfloat eyeZ = 2;

static GLfloat centerX = 0;
static GLfloat centerY = 0;
static GLfloat centerZ = 0;

static GLfloat upX = 0;
static GLfloat upY = 1;
static GLfloat upZ = 0;

static GLfloat vX = 0;
static GLfloat vY = 0;
static GLfloat vZ = 0;

static int Mx = 0, My = 0;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.3, 0.3, 0.7);
	glMatrixMode(GL_PROJECTION); // change to projection view
	glLoadIdentity(); // load identity matrix
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW); // restore to model view
	glLoadIdentity(); // load identity matrix
}

void mouse_handler(int x, int y)
{
	vX = centerX - eyeX;
	vZ = centerZ - eyeZ;

	if (x - Mx > 0)
	{
		centerX = eyeX + cos(TURN)*vX - sin(TURN)*vZ;
		centerZ = eyeZ + sin(TURN)*vX + cos(TURN)*vZ;
	}
	else
	{
		centerX = eyeX + cos(-TURN)*vX - sin(-TURN)*vZ;
		centerZ = eyeZ + sin(-TURN)*vX + cos(-TURN)*vZ;
	}

	if (y - My > 0)
	{
		centerX -= vX * (TURN * 3);
		centerZ -= vZ * (TURN * 3);
	}
	else
	{
		centerX += vX * (TURN * 3);
		centerZ += vZ * (TURN * 3);
	}

	Mx = x;
	My = y;
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	vX = centerX - eyeX;
	vY = centerY - eyeY;
	vZ = centerZ - eyeZ;

	if (key == 'w')
	{
		eyeX += vX*WALK;
		eyeZ += vZ*WALK;
		centerX += vX*WALK;
		centerZ += vZ*WALK;
		printf("W\n");
	}
	if (key == 's')
	{
		eyeX -= vX*WALK;
		eyeZ -= vZ*WALK;
		centerX -= vX*WALK;
		centerZ -= vZ*WALK;
		printf("S\n");
	}

	if (key == 'a')
	{
		GLfloat x = vY*upZ - vZ*upY;
		GLfloat z = vX*upY - vY*upX;

		eyeX -= x*WALK;
		eyeZ -= z*WALK;
		centerX -= x*WALK;
		centerZ -= z*WALK;

		printf("A\n");
	}
	if (key == 'd')
	{
		GLfloat x = vY*upZ - vZ*upY;
		GLfloat z = vX*upY - vY*upX;

		eyeX += x*WALK;
		eyeZ += z*WALK;
		centerX += x*WALK;
		centerZ += z*WALK;

		printf("D\n");
	}
	if (key == 'D') //default view
	{
		eyeX = 2;
		eyeY = 2;
		eyeZ = 2;

		centerX = 0;
		centerY = 0;
		centerZ = 0;

		upX = 0;
		upY = 1;
		upZ = 0;
	}

	glutPostRedisplay();
}

void sound()
{
	sndPlaySound(TEXT("./Kirby.wav"), SND_FILENAME | SND_ASYNC | SND_LOOP);

	if(!music)
		sndPlaySound(NULL, SND_ASYNC);
}

void MyDisplay()
{
	init();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	glutWireTeapot(1.0);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("MIRO");
	glutKeyboardFunc(keyboard_handler); 
	glutPassiveMotionFunc(mouse_handler);
	init();
	if (start)
	{
		sound();
		start = false;
	}
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}