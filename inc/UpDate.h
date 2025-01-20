#ifndef UPDATE_H
#define UPDATE_H

#include "app.h"
#include "Settings.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDLWIN.h"
#include "Bull.h"
#include "Inputs.h"
#include "Enemy.h"

int MainUpDate();

void RenderPresent( SDL_Renderer* rend );

void DestroyTexture( SDL_Texture* texMap , SDL_Texture* texPlay , SDL_Texture* texText );

void CollisionInEnemys( Bull* playerBull , Enemys* enemysList, int countList , int limitWidth , int limitHeight );

void CollisionInPlayer( Bull* bull , SDL_Rect destPlay , int limitWidth , int limitHeight );

#endif
