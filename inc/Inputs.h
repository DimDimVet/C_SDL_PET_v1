#ifndef INPUTS_H
#define INPUTS_H

#include "Settings.h"
#include <stdio.h>
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDLWIN.h"
#include "Bull.h"

void InputsUpdate( SDL_Event* event , int* close , SDL_Rect* destPlay, Bull* playerBull , int* angle );

#endif


