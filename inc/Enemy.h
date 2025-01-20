#ifndef ENEMY_H
#define ENEMY_H

#include "Settings.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDLWIN.h"
#include "Bull.h"

typedef struct
{
	SDL_Texture* texEnemy;
	SDL_Rect destEnemy;
	int angle;
	bool isKill;

}Enemys;

typedef struct
{
	int ignorPosX;
	int ignorPosY;

}IgnPos;


Enemys* InitEnemys( int countEnemys , char* pathPng , SDL_Renderer* rend , int width , int height );
int RandomPosition( int min , int max );
void MoviEnemys( Enemys* enemysList , int countEnemys , SDL_Renderer* rend );

#endif
