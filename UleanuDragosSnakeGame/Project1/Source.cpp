#include <GL/freeglut.h> 
#include <GL/GL.h>
#include <GL/glut.h>
#include "Draw.h";
#include <stdlib.h>
#include <irrKlang.h>
#include<iostream>
using namespace irrklang;


#define COLUMNS 40
#define ROWS 40
int FPS = 10;

extern short sDirection;
bool gameOver = false;
int score = 0;
ISoundEngine* sound = createIrrKlangDevice();

//Iluminare; Delete if necessary;
GLfloat qaBlack[] = { 0.0,0.0,0.0,1.0 };
GLfloat qaGreen[] = { 0.1,1.0,0.0,1.0 };
GLfloat qaWhite[] = { 1.0,1.0,1.0,1.0 };
GLfloat qaRed[] = { 1.0,0.0,0.0,1.0 };

GLfloat qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
GLfloat qaSpecularLight[] = { 1.0,1.0,1.0,1.0 };
GLfloat emitLight[] = { 0.9,0.9,0.9,0.01 };
GLfloat Noemit[] = { 0.0,0.0,0.0,1.0 };
GLfloat qaLightPosition[] = { 0.0, 0, 0.0, 0.1 };
//Delete if necessary;



void displayCallback();
void timerCallback(int);
void keyboardCallback(int, int, int);
void reshapeCallback(int, int);
void initLighting();

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	
	initGrid(COLUMNS, ROWS);
	glShadeModel(GL_SMOOTH);
	
}


int main(int argc, char **argv)
{

	
	glutInit(&argc, argv); //initializare Glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //initializare Display
	glutInitWindowSize(500, 500);
	glutCreateWindow("Snake Definitive Edition");
	
	glutDisplayFunc(displayCallback); //callback display
	glutReshapeFunc(reshapeCallback);
	glutTimerFunc(0, timerCallback, 0);
	glutSpecialFunc(keyboardCallback);
	init();
	sound->play2D("media/sd1.mp3", true);
	glutMainLoop();
	return 0;

}

int index = 0;

void displayCallback()
{
	glMatrixMode(GL_MODELVIEW); //delete if necessary;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); //delete if necessary;

	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();
	if (gameOver)
	{
		char score1[10];
		_itoa_s(score, score1, 10);
		char message[50] = "Your score: ";
		strcat_s(message, score1);
		sound->stopAllSounds();
		sound->play2D("media/gameOver.wav");
		MessageBox(NULL, message, "GAME OVER", 0);
		
		exit(0);
	}
}

void reshapeCallback(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);


}

void timerCallback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timerCallback,0);

}

void keyboardCallback(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (sDirection != DOWN)
		{
			sDirection = UP;
		}
		break;
	case GLUT_KEY_DOWN:
		if (sDirection != UP)
		{
			sDirection = DOWN;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT)
		{
			sDirection = RIGHT;
		}
		break;
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT)
		{
			sDirection = LEFT;
		}
		break;
	case GLUT_KEY_F2:
		initLighting();
		break;
	
	case GLUT_KEY_F1:
		exit(0);
		break;

	}


}
void initLighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}