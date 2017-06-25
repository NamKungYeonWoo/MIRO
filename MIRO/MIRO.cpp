// MIRO.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#pragma once
#include "stdafx.h"
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment (lib, "fmodex_vc.lib")

using namespace FMOD;

#pragma warning(disable:4996)

#define WALK 0.8
#define TURN 1.0

int map[30][30] = { { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
{ 1,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3 },
{ 3,4,3,0,3,3,3,0,3,0,0,3,6,3,4,3,3,0,3,3,4,3,0,3,3,3,3,0,3,3 },
{ 3,3,3,0,3,0,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,3,3 },
{ 3,3,3,0,0,0,3,0,0,0,0,0,0,0,3,3,0,0,0,3,3,0,5,3,3,3,3,3,3,3 },
{ 3,3,3,3,3,3,3,0,0,3,0,3,3,0,0,0,0,3,0,3,3,0,3,3,3,0,0,0,0,3 },
{ 3,3,0,0,0,0,0,0,0,4,0,3,3,3,3,3,3,3,0,3,3,0,3,3,3,0,3,3,3,3 },
{ 3,3,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,3,0,0,3,0,3,0,0,0,0,3,3,3 },
{ 3,3,0,3,0,3,0,0,0,3,0,3,0,3,0,3,3,3,3,0,3,0,3,0,3,3,0,3,3,3 },
{ 3,3,0,3,0,0,0,3,0,3,0,3,0,3,4,3,0,3,3,0,3,0,3,0,4,3,0,4,3,3 },
{ 3,3,0,3,3,3,3,6,0,3,0,3,0,3,0,3,0,0,0,0,3,0,3,0,0,3,0,3,3,3 },
{ 3,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,3,0,3,0,4,3,3,3,0,3,3,3 },
{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,0,3,0,3,0,0,0,0,0,3,3 },
{ 3,3,3,0,0,0,0,0,0,0,0,0,3,3,0,3,3,3,3,0,3,0,3,0,3,0,3,3,3,3 },
{ 3,3,3,0,3,5,3,0,3,3,3,0,3,3,0,0,0,0,3,0,0,0,3,0,3,0,5,3,3,3 },
{ 3,0,0,0,3,3,3,0,4,3,5,0,3,3,0,3,3,0,4,0,3,3,3,0,3,0,3,3,3,3 },
{ 3,0,3,0,3,3,3,0,0,0,0,0,3,3,3,6,3,0,3,0,6,3,3,3,3,0,0,0,3,3 },
{ 3,0,3,0,3,3,3,0,3,3,0,3,3,0,0,0,0,0,3,0,0,0,3,0,3,0,3,3,3,3 },
{ 3,0,3,0,4,3,3,0,3,3,0,5,3,3,3,3,3,3,3,0,3,0,0,0,3,0,3,3,3,3 },
{ 3,0,3,0,3,3,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,3,0,3,3,0,3 },
{ 3,0,3,0,0,0,0,0,3,0,4,3,3,3,3,5,0,3,3,3,0,4,3,0,4,0,3,3,0,3 },
{ 3,0,3,0,3,3,3,0,3,0,3,0,0,0,3,3,0,0,0,0,0,3,0,0,3,0,3,3,0,3 },
{ 3,0,3,0,3,3,3,0,3,0,3,0,3,0,0,0,0,4,3,3,0,3,3,0,3,0,0,0,0,3 },
{ 3,0,3,0,3,3,3,0,3,0,3,3,3,3,3,3,0,3,3,0,0,0,3,3,3,3,3,3,0,3 },
{ 3,0,3,0,3,3,3,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,3 },
{ 3,0,3,0,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,4,0,3,0,3 },
{ 3,0,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,3,3,0,3,3,3,0,3,0,3,0,3 },
{ 3,0,0,0,3,3,5,3,3,3,4,3,3,3,3,3,3,0,3,0,0,0,0,0,0,3,0,0,0,3 },
{ 3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,3,3,3,3,4,0,3,3,3 },
{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3 } };

int width = 1200, height = 1000;
int w, h;
int window;
int pictureNum, leftQuizNum, rightQuizNum;

bool music = true, start = true, stop = false;
static int Mx = 0, My = 0;

GLuint loadTex(char *);
GLuint normalFloor, normalWall;
GLuint startFloor;
GLuint picture[10];
GLuint leftQuiz[6];
GLuint rightQuiz[4];

float a = 0.0, b = 1.0; // to save a vertex3f value cu
float c = 0.0, d = 1.0;// to save a vertex3f value  fl0

System* pSystem;
Sound* pSound;
Channel* pChannel;

void loadTexture();
void randomNum();

GLfloat angX = 0.0;
GLfloat angY = 0.0;
GLfloat tmp_ang = 0.0;
GLdouble X = 3.0;
GLdouble Y = 0.0;
GLdouble Z = 1.2;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.3, 0.3, 0.7);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, 1.0, 0.01, 100.0);
	float ambientLight[] = { 2.0f, 2.0f, 2.0f, 2.0f };         // 주변광
	float diffuseLight[] = { 2.5f, 2.5f, 2.5f, 2.5f };      // 분산광
	float lightPosition[4][4] = { { 7.0f, 50.0f, 0.0f, 1.0f } ,{ 0.0f, 55.0f, 0.0f, 0.0f } ,{ 0.0f, 50.0f, 7.0f, 0.0f } ,{ 0.0f, 50.0f, 0.0f, 7.0f } }; // 광원위치

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	for (int i = 0; i < 4; i++) 
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition[i]);

	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void loadTexture()
{
	normalFloor = loadTex("wood.bmp");
	startFloor = loadTex("start.bmp");
	normalWall = loadTex("brick.bmp");
	picture[0] = loadTex("pic1.bmp");
	picture[1] = loadTex("pic2.bmp");
	picture[2] = loadTex("pic3.bmp");
	picture[3] = loadTex("pic4.bmp");
	picture[4] = loadTex("pic5.bmp");
	picture[5] = loadTex("pic6.bmp");
	picture[6] = loadTex("pic7.bmp");
	picture[7] = loadTex("pic8.bmp");
	picture[8] = loadTex("pic9.bmp");
	picture[9] = loadTex("pic10.bmp");
	leftQuiz[0] = loadTex("leftQ1.bmp");
	leftQuiz[1] = loadTex("leftQ2.bmp");
	leftQuiz[2] = loadTex("leftQ3.bmp");
	leftQuiz[3] = loadTex("leftQ4.bmp");
	leftQuiz[4] = loadTex("leftQ5.bmp");
	leftQuiz[5] = loadTex("leftQ6.bmp");
	rightQuiz[0] = loadTex("RightQ1.bmp");
	rightQuiz[1] = loadTex("RightQ2.bmp");
	rightQuiz[2] = loadTex("RightQ3.bmp");
	rightQuiz[3] = loadTex("RightQ4.bmp");
}

void mouse_handler(int x, int y)
{
	GLdouble dX = x - Mx;
	GLdouble dY = y - My;

	if (dX < 0)
	{
		angX -= TURN;
		if (angX > 360.0) angX -= 360.0;
		if (angX < 0) angX += 360.0;
	}
	else
	{
		angX += TURN;
		if (angX < 0.0) angX += 360.0;
		if (angX > 360.0) angX -= 360.0;
	}

	/*if (dY < 0)
	{
		angY -= TURN;
		if (angY > 360.0) angY -= 360.0;
		if (angY < 0) angY += 360.0;
	}
	else
	{
		angY += TURN;
		if (angY < 0.0) angY += 360.0;
		if (angY > 360.0) angY -= 360.0;
	}*/

	Mx = x;
	My = y;
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'w')
		{
			printf("W\n");
	
			int x = -1 * (int)((X - (0.1*sin(angX*(3.14 / 180)))) / 0.8);
			int z = (int)((Z + (0.1*cos(angX*(3.14 / 180)))) / 0.8);

			printf("x: %d z: %d map: %d\n", x, z, map[z][x]);
			printf("X: %.2lf Z: %.2lf\n\n", X, Z);

			if (x >= 0 && x < 30 && z >= 0 && z < 30) 
			{
				if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
					X -= 0.1*sin(angX*(3.14 / 180));
				if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
					Z += 0.1*cos(angX*(3.14 / 180));
			}
			else 
			{
				X -= 0.1*sin(angX*(3.14 / 180));
				Z += 0.1*cos(angX*(3.14 / 180));
			}
		}
	
		if (key == 's')
		{
			printf("S\n");
	
			int x = -1 * (int)((X + (0.1*sin(angX*(3.14 / 180)))) / 0.8);
			int z = (int)((Z - (0.1*cos(angX*(3.14 / 180)))) / 0.8);

			printf("x: %d z: %d map: %d\n", x, z, map[z][x]);
			printf("X: %.2lf Z: %.2lf\n\n", X, Z);

			if (x >= 0 && x < 30 && z >= 0 && z < 30) 
			{
				if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
					X += 0.1*sin(angX*(3.14 / 180));
				if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
					Z -= 0.1*cos(angX*(3.14 / 180));
			}
			else 
			{
				X += 0.1*sin(angX*(3.14 / 180));
				Z -= 0.1*cos(angX*(3.14 / 180));
			}
		}
	
		if (key == 'a')
		{
			angX -= TURN * 3;
			if (angX > 360.0) angX -= 360.0;
			if (angX < 0) angX += 360.0;
	
			printf("A\n");
		}
	
		if (key == 'd')
		{
			angX += TURN * 3;
			if (angX < 0.0) angX += 360.0;
			if (angX > 360.0) angX -= 360.0;
	
			printf("D\n");
		}
	
		if (key == 27)
		{
			glutDestroyWindow(window);
			printf("\n--END--\n");
			exit(0);
		}
	

	glutPostRedisplay();
}

void sound()
{
	System_Create(&pSystem);
	pSystem->init(1, FMOD_INIT_NORMAL, NULL);

	pSystem->createSound(
		"Kirby.wav",
		FMOD_LOOP_NORMAL | FMOD_HARDWARE,
		NULL,
		&pSound
	);
	FMOD_System_PlaySound((FMOD_SYSTEM*)pSystem, FMOD_CHANNEL_FREE, (FMOD_SOUND*)pSound, NULL, (FMOD_CHANNEL**)pChannel);
}

void floor(float x1, float x2, float y1, float z1, float z2, int texNum)
{

	glEnable(GL_TEXTURE_2D);
	if (texNum == 0)glBindTexture(GL_TEXTURE_2D, normalFloor);
	else glBindTexture(GL_TEXTURE_2D, startFloor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(c, c);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(d, c);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(d, d);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(c, d);
	glVertex3f(x2, y1, z2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void randomNum()
{
	pictureNum = rand() % 10;
	leftQuizNum = rand() % 6;
	rightQuizNum = rand() % 4;
}

void wall(float x1, float x2, float y1, float y2, float z1, float z2, int texNum)
{
	srand(time(NULL));
	glEnable(GL_TEXTURE_2D);

	if (texNum == 3)glBindTexture(GL_TEXTURE_2D, normalWall);
	else if (texNum == 4)
		glBindTexture(GL_TEXTURE_2D, picture[pictureNum]);
	else if (texNum == 5)
		glBindTexture(GL_TEXTURE_2D, leftQuiz[leftQuizNum]);
	else if (texNum == 6)
		glBindTexture(GL_TEXTURE_2D, rightQuiz[rightQuizNum]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(b, a);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(0.0, b);
	glVertex3f(x1, y2, z1);// 오른쪽

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(b, a);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(a, b);
	glVertex3f(x1, y2, z2);//왼쪽 면

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(b, a);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(a, b);
	glVertex3f(x1, y2, z2);// 아마 윗면

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(b, a);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(b, b);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(a, b);
	glVertex3f(x1, y2, z2);//정면

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(b, a);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(a, b);
	glVertex3f(x2, y2, z2);
	//뒷면

	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void MyDisplay()
{
	init();

	glMatrixMode(GL_MODELVIEW);

	glRotatef(angX, 0.0, 1.0, 0.0);
	glRotatef(angY, 1.0, 0.0, 0.0);
	glTranslatef(X, Y, Z);

	for (int i = 0; i < 30; i++) 
	{
		for (int j = 0; j < 30; j++) 
		{
			if (map[j][i] >= 3) 
				wall(0.8*i, 0.8*(i + 1), -0.4, 0.4, -0.8*j, -0.8*(j + 1), map[j][i]);
			else  
				floor(0.8*i, 0.8*(i + 1), -0.4, -0.8*j, -0.8*(j + 1), map[j][i]);
		}
	}

	glutSwapBuffers();
}

char *img_read(char * name)
{
	FILE *f = fopen(name, "rb");
	if (f == NULL) exit(0);
	int of;
	fseek(f, 10, SEEK_SET);
	fread(&of, sizeof(int), 1, f);
	fseek(f, 4, SEEK_CUR);
	fread(&w, sizeof(int), 1, f);
	fread(&h, sizeof(int), 1, f);

	fseek(f, of, SEEK_SET);
	int j = 0;
	int by = ((w * 3 + 3) / 4) * 4 - (w * 3 % 4);
	char * tmp_m = (char *)malloc(sizeof(char) * by * h);
	char *m2 = (char *)malloc(sizeof(char) * w * h * 3);

	fread(tmp_m, sizeof(char) * by * h, 1, f);
	int x, y, i;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			for (i = 0; i < 3; i++)
				m2[3 * (w*y + x) + i] = tmp_m[3 * (w*y + x) + (2 - i)];
		}
	}
	free(tmp_m);
	fclose(f);
	return m2;
}

GLuint loadTex(char *c)
{
	char *wa = img_read(c);
	GLuint texid;

	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, wa);
	free(wa);

	return texid;
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	window = glutCreateWindow("MIRO");
	glutFullScreen();
	glutKeyboardFunc(keyboard_handler);
	glutMotionFunc(mouse_handler);

	init();

	if (start && !stop)
	{
		angX = 90;
		printf("--START--\n\n");
		sound();
		loadTexture();
		randomNum();
		start = false;
	}
	else
	{
		pSound->release();
		pSystem->release();
		pSystem->close();
	}

	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}