#ifndef BULL_H
#define BULL_H

#include "Settings.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDLWIN.h"

enum Angle
{
	Left = 180 ,
	Right = 0 ,
	Down = 90 ,
	Up = -90
};

typedef struct Bull
{
	bool isRun;
	int count;
	char* pathBULLPNG;
	char* pathFIREPNG;

	SDL_Rect parentDest;
	double angle;
	int offset;

	SDL_Texture* texBull;
	SDL_Rect destBull;

	SDL_Texture* texFire;
	SDL_Rect destFire;

	int limitWidth;
	int limitHeight;

}Bull;

void MoviBull( Bull* bull , SDL_Renderer* rend , SDL_Rect parentDest , int angle , int offset );
Bull* InitBulls( int count , char* pathBULLPNG , char* pathFIREPNG , int limitHeight , int limitWidth );

#endif
