#include "UpDate.h"

int MainUpDate()
{
	char textScore[10];

	SDL_Window* win;
	win = InitWin(NAME_WIN, WIN_WIDTH, WIN_HEIGHT);

	// �������� �������
	SDL_Renderer* rend;
	rend = InitRender(win);

	// �������� �������� �� ��������
	SDL_Texture* texMap = InitTexturePng(rend, path_GND_PNG);
	SDL_Texture* texPlay = InitTexturePng(rend, path_TNK_PNG);
	// �������� �������� �� ��������
	Enemys* enemysList = InitEnemys(count_ENEMY, path_ENEMY_PNG, rend, WIN_WIDTH, WIN_HEIGHT);

	// �������� ������
	TTF_Font* font = TTF_OpenFont(path_Font, size_Font);
	// �������� �����
	SDL_Color textColor = { 255, 255, 255, 255 };
	// �������� �������� �� ��������
	SDL_Texture* texText = InitText(rend, LABEL_STATIC_TEXT, font, textColor);
	SDL_Texture* texTextDinamic = InitText(rend, "", font, textColor);;

	// �������� ������� �������� � �������
	SDL_Rect destPlay = InitDest(texPlay);

	int angle = 0; // ���� ��������
	int* angleUkz = &angle;

	// controls loop
	int close = 0;
	int* closeUkz = &close;

	// ������ � ������ �������
	destPlay.w /= scale_PLAYER_PNG;
	destPlay.h /= scale_PLAYER_PNG;
	// ������� �� ���� �������
	destPlay.x = (WIN_WIDTH - destPlay.w) / 2;
	destPlay.y = (WIN_HEIGHT - destPlay.h) / 2;

	//������ ������� ������� (����+���)
	SDL_Event event;

	//Bull player
	Bull playerBull;
	playerBull.isRun = false;
	playerBull.count = 0;
	playerBull.pathBULLPNG = path_BULL_PNG;
	playerBull.pathFIREPNG = path_FIRE_PNG;
	playerBull.limitHeight = WIN_HEIGHT;
	playerBull.limitWidth = WIN_WIDTH;

	//Bull enemy
	Bull* enemyBulls = InitBulls(count_ENEMY, path_BULL_PNG, path_FIRE_PNG, WIN_HEIGHT, WIN_WIDTH);
	int countStartEnemyBull = 0;

	// animation loop
	while (!close)
	{
		//������� �������
		SDL_RenderClear(rend);

		snprintf(textScore, sizeof textScore, "Score %d", ScorePlayer());

		//�������� � ������ �������� �������� (����)
		RenderTexturePng(texMap, rend, WIN_WIDTH, WIN_HEIGHT);

		//�������� � ������ �������� ������ (��������� �����)
		RenderTextureText(texText, rend, WIN_WIDTH, WIN_HEIGHT - (WIN_HEIGHT- position_HEIGHT_Text1));
		//�������� � ������ �������� ������ (���������� �����)
		UpDateRenderTextureText(texTextDinamic, rend, textScore, font, textColor, WIN_WIDTH+(WIN_WIDTH- position_WIDTH_Text2), WIN_HEIGHT + (WIN_HEIGHT - position_HEIGHT_Text2));


		/////Enemy
		MoviEnemys(enemysList, count_ENEMY, rend);

		for (int i = 0; i < count_ENEMY; i++)
		{
			if (enemyBulls[i].isRun & !enemysList[i].isKill)
			{
				CollisionInPlayer(&enemyBulls[i], destPlay, WIN_WIDTH, WIN_HEIGHT);
				MoviBull(&enemyBulls[i], rend, enemysList[i].destEnemy, enemysList[i].angle, SPEED_BULL_ENEMY);
			}
			else
			{
				countStartEnemyBull++;
				if (countStartEnemyBull > 100)
				{
					countStartEnemyBull = 0;
					enemyBulls[i].isRun = true;
				}

			}
		}
		/////EndEnemy

		/////Player
		//�������� � ������ �������� �������� � �������(������) (�������� �������)
		UpDateRenderTexturePng(texPlay, rend, destPlay, angle);
		//����������+���
		while (SDL_PollEvent(&event))
		{
			InputsUpdate(&event, closeUkz, &destPlay, &playerBull, angleUkz);
		}

		BoundaryY(&destPlay, WIN_HEIGHT);
		BoundaryX(&destPlay, WIN_WIDTH);

		if (playerBull.isRun)
		{
			CollisionInEnemys(&playerBull, enemysList, count_ENEMY, WIN_WIDTH, WIN_HEIGHT);
			MoviBull(&playerBull, rend, destPlay, angle, SPEED_BULL_PLAYER);
		}
		else
		{
			playerBull.limitWidth = WIN_WIDTH;
			playerBull.limitHeight = WIN_HEIGHT;
		}
		///// EndPlayer

		RenderPresent(rend);
	}

	// �������� ��������
	DestroyTexture(texMap, texPlay, texText);

	CloseSDL(font, rend, win);

	return 0;
}
//
void RenderPresent(SDL_Renderer* rend)
{
	SDL_RenderPresent(rend);
	// calculates to 60 fps
	SDL_Delay(1000 / 60);
}

void DestroyTexture(SDL_Texture* texMap, SDL_Texture* texPlay, SDL_Texture* texText)
{
	SDL_DestroyTexture(texMap);
	SDL_DestroyTexture(texPlay);
	SDL_DestroyTexture(texText);
}

void CollisionInEnemys(Bull* bull, Enemys* enemysList, int countList, int limitWidth, int limitHeight)
{
	for (int i = 0; i < countList; i++)
	{
		if (SDL_HasIntersection(&bull->destBull, &enemysList[i].destEnemy))
		{
			if (!enemysList[i].isKill)
			{
				bull->limitWidth = enemysList[i].destEnemy.x;
				bull->limitHeight = enemysList[i].destEnemy.y;
				enemysList[i].isKill = true;
				LogicScorePlayer(price_SCORE_ENEMY);
				break;
			}
		}
	}
}

void CollisionInPlayer(Bull* bull, SDL_Rect destPlay, int limitWidth, int limitHeight)
{
	if (SDL_HasIntersection(&bull->destBull, &destPlay))
	{
		bull->limitWidth = destPlay.x;
		bull->limitHeight = destPlay.y;
	}
	else
	{
		bull->limitWidth = limitWidth;
		bull->limitHeight = limitHeight;
	}
}

