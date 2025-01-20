#ifndef APP_H
#define APP_H

#include "Settings.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDLWIN.h"
#include "Bull.h"
#include "UpDate.h"

int SummPlayerScore;

void LogicScorePlayer( int score );
int ScorePlayer();

#endif
