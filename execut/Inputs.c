#include "Inputs.h"

void InputsUpdate(SDL_Event* event, int* close, SDL_Rect* destPlay, Bull* playerBull, int* angle)
{
	switch (event->type)
	{

	case SDL_QUIT:
		// handling of close button
		*close = 1;
		break;

	case SDL_MOUSEBUTTONDOWN:

		if (event->button.button == SDL_BUTTON_LEFT)
		{
			printf("Press left button mouse (%d, %d)\n", event->button.x, event->button.y);

			if (playerBull->isRun == false)
			{
				playerBull->isRun = true;
			}
		}

		if (event->button.button == SDL_BUTTON_RIGHT)
		{
			printf("Press right button mouse (%d, %d)\n", event->button.x, event->button.y);
		}
		break;

	case SDL_KEYDOWN:

		printf("Press button -> %s\n", SDL_GetKeyName(event->key.keysym.sym));

		// keyboard API for key pressed
		switch (event->key.keysym.scancode)
		{
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			destPlay->y -= SPEED_PLAYER;
			*angle = Up;
			break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			destPlay->x -= SPEED_PLAYER;
			*angle = Left;
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			destPlay->y += SPEED_PLAYER;
			*angle = Down;
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			destPlay->x += SPEED_PLAYER;
			*angle = Right;
			break;

		default:
			break;
		}

	default:
		break;
	}

}
