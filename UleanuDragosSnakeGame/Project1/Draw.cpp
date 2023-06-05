#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "Draw.h"
#include <ctime>
#include <irrKlang.h>
using namespace irrklang;


int gridX, gridY;
int snakeLength = 5;
short sDirection = RIGHT;
bool food = true;
int foodX, foodY;
int posX[60] = { 20,20,20,20,20 }, posY[60] = { 20,19,18,17,16 };
extern bool gameOver;
extern int score;
extern int FPS;
extern ISoundEngine* sound;


void initGrid(int x, int y)
{
	gridX = x;
	gridY = y;

}

void unit(int x, int y)
{
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
	{
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else
	{
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}
	
	
	//glLineWidth(1.0);
	//glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);

	glEnd();
}

void drawGrid()
{

	for (int x = 0; x < gridX; x++)
	{
		for (int y = 0; y < gridY; y++)
		{
			unit(x, y);
		}
	}

}

void drawFood()
{
	if (food == true)
	{
		random(foodX, foodY);
	}
	food = false;
	glColor3f(1.0, 1.0, 1.0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1);

}

void drawSnake()
{
	for (int i = snakeLength - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];

	}
	if (sDirection == UP)
	{
		posY[0]++;
	}
	else if (sDirection == DOWN)
	{
		posY[0]--;
	}
	else if (sDirection == RIGHT)
	{
		posX[0]++;
	}
	else if (sDirection == LEFT)
	{
		posX[0]--;
	}

	for (int i = 0; i < snakeLength; i++)
	{
		if (i == 0)
		{
			glColor3f(0.0, 0.0, 1.0);
		}
		else
		{
			glColor3f(0.0, 1.0, 0.0);
		}
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}
	//glColor3f(0.2, 0.0, 0.6);
	//glRectd(posX, posY, posX + 1, posY + 1);
	if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
	{
		gameOver = true;
	}

	if (posX[0] == foodX && posY[0] == foodY)
	{
		sound->play2D("media/boop.wav");
		score++;
		snakeLength++;
		FPS++;
		if (score % 10 == 0)
		{
			sound->play2D("media/yaay.wav");
		}

		if (snakeLength > MAX)
		{
			snakeLength = MAX;
			gameOver = true;
		}
		food = true;
		
	}
	for (int i = 1; i < snakeLength; i++)
	{
		if (posX[0] == posX[i] && posY[0] == posY[i])
		{
			gameOver = true;
		}
	}

}

void random(int &x, int &y)
{
	int maximX = gridX - 2;
	int maximY = gridY - 2;
	int minim = 1;
	srand(time(NULL));
	x = minim + rand() % (maximX - minim);
	y = minim + rand() % (maximY - minim);
}
