// snake.cpp :  console game created by DAP.
//

#include "stdafx.h"
#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;


bool solidwall=false;					// make true if u want toend game on hit the wall
bool gmover;
const int width = 30;
const int height = 20;
int x, y, fx, fy, score;
int tailX[100], tailY[100];
int tail;

enum direction {
	STOP=0,
	LEFT, RIGHT, UP, DOWN
};
direction dir;

void setup()
{

	cout << "PRESS 'W' 'A' 'S' 'D'  TO SWITCH TO DIR YOUR SNAKE AND 'X' TO EXIT GAME"<<endl;
	Sleep(3000);
	gmover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fx = rand() % (width - 1);
	fy = rand() % (height-1);
	score = 0;
	

}

void draw()
{
	system("cls");



	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i <=height-1; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (j == 0)
				cout << "#";
			if (j == x && i == y)
				cout << "O";
			else if (j == fx && i == fy)
				cout << "F";
			else 
			{
				bool print = false;
				for (int k = 0; k < tail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			
				
			if (j == width-1)
				cout << "#";
		}
		cout << endl;
	}
	


	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;


	cout << "SCORE:" << score << endl;
}

void input()
{
	if (_kbhit()) {
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gmover = true;
			break;
		default:
			cout << endl << "couldn't catch anything ....enter 'W','A','S','D'   ...!!!" << endl;
			Sleep(500);
			break;
		}
	}

}	

void logic()
{

	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int tail2X, tail2Y;
	for (int i = 1; i < tail; i++)
	{
		tail2X = tailX[i];
		tail2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tail2X;
		prevY = tail2Y;
	}


	switch (dir)
	{
	case STOP:
		break;

	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (solidwall)
	{
		if (x < 0 || x == width || y < 0 || y == height)
			gmover = true;

	}
	else
	{
		if (x >= width) x = 0; else if (x < 0) x = width - 1;
		if (y >= height) y = 0; else if (y < 0) y = height - 1; 
	}

	if (x == fx && y == fy)
	{
		score += 10;
		fx = rand() % (width - 1);
		fy = rand() % (height - 1);
		tail++;
		
	}

	for (int i = 0; i < tail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gmover = true;
	}

	
}


int main()
{

	setup();
	while (!gmover) {
		
		draw();
		input();
		logic();

		int x = score / 50;
		x = (100 - 15 * x) > 0 ? (100 - 15 * x) : 0;
		Sleep(x);

		int speed = 3 *(score/10);
		cout << "speed :" << speed;
	}

	if (gmover)
	{
		cout << "GAME OVER MR. ..!!" << endl;
		cout << "SCORE :" << score << endl;
		Sleep(1000);
	}
		
    return 0;
}