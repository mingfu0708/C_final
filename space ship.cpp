#include <stdlib.h> //Standard c and c++ libraries
#include <conio.h>
#include <stdio.h>
#include <windows.h> // To take control over the terminal
#include <list>
#ifndef SPACE_SHIP
#define SPACE_SHIP
#include "space ship.h"
#include "drawing.h" 
#endif
using namespace std;
#define UP    72 // arrow keys' ascii numbers
#define LEFT  75
#define RIGHT 77
#define DOWN  80

	bool SpaceShip::isDead()
	{
		DrawSpaceShipInfo(); // It's annoying to die and still see a heart on the screen
		return imDead;
	}
	
	SpaceShip::SpaceShip(int _x, int _y)
	{
		x = _x;
		y = _y;
		hp = 3; // I designed the game to have 3 lifes
		energy = 5; // And 5 energy points every life
		imDead = false; // By default you are not dead
	}
	
	void SpaceShip::DrawSpaceShipInfo()
	{ // Displays HP and energy points, I aligned them with the labels printed in DrawGameLimits
		gotoxy(5, 1); printf("     ");
		for(int i = 0; i < hp; i++)
		{
			gotoxy(5 + i, 1); printf("%c", 64);
		}
		gotoxy(23, 1); printf("     ");
		for(int i = 0; i < energy; i++)
		{
			gotoxy(23 + i, 1); printf("%c", 64);
		}
	}
	
	void SpaceShip::Draw()
	{ // This is our spaceship
		gotoxy(x,y);     printf( "  %c  ", 168 );
		gotoxy(x,y + 1); printf( "  %c  ", 65);
		gotoxy(x,y + 2); printf("%c%c%c%c%c",65, 65, 65, 65, 65);
	}
	
	void SpaceShip::Erase()
	{ // This was or spaceship
		gotoxy(x,y);     printf("     ");
		gotoxy(x,y + 1); printf("     ");
		gotoxy(x,y + 2); printf("     ");
	}
	
	void SpaceShip::Damage()
	{ // Triggered by the asteroids that hit the spaceship
		energy--;
		if(energy == 0)
		{
			Explosion();
		}
		else
		{
			Erase(); // You can omit this part, is meant to visually tell you that you were hit
			gotoxy(x,y);     printf("  *  ");
			gotoxy(x,y + 1); printf("  *  ");
			gotoxy(x,y + 2); printf("*****");
			Sleep(100);
		}
	}
	void SpaceShip::Explosion()
	{ // When you lose a heart :c
		hp--;
		Erase();
		gotoxy(x,y);     printf("  *  ");
		gotoxy(x,y + 1); printf("  *  ");
		gotoxy(x,y + 2); printf("*****");
		Sleep(100);
		Erase();
		gotoxy(x,y);     printf(" * * ");
		gotoxy(x,y + 1); printf("* * *");
		gotoxy(x,y + 2); printf(" * * ");
		Sleep(100);
		Erase();
		gotoxy(x,y);     printf("*   *");
		gotoxy(x,y + 1); printf(" * * ");
		gotoxy(x,y + 2); printf("* * *");
		Sleep(100);
		if(hp > 0)
		{ // If you still have a heart or more
			energy = 5;
		}
		else
		{ // If you don't
			imDead = true;
		}
	}
	
	void SpaceShip::Move()
	{ // The main function of the spaceship
		if(kbhit())
		{ // If you move the spaceship
			Erase(); // Look I'm invisible
			char key = getch(); // What did you type?
			switch(key)
			{ // Checks if the spaceship won't leave the game boundaries
				case LEFT:  if(x > 2)      x -= 1; break;
				case RIGHT: if(x + 4 < 77) x += 1; break;
				case UP:    if(y > 3)      y -= 1; break;
				case DOWN:  if(y + 2 < 22) y += 1; break;
			}
		}
		Draw(); // The spaceship is drawn regardless if you moved it or not, if you did then it will appear in it's new position.
	}
