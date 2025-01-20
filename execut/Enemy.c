#include "Enemy.h"

Enemys* InitEnemys(int countEnemys, char* pathPng, SDL_Renderer* rend, int width, int height)
{
	Enemys* enemysList;
	IgnPos* ignPos;

	if (countEnemys <= 0)
	{
		printf("error count enemys");
		return 0;
	}

	srand(time(0));
	enemysList = malloc(countEnemys * sizeof(Enemys));
	ignPos = malloc(countEnemys * sizeof(IgnPos));

	if (ignPos != NULL)
	{
		for (int i = 0; i < countEnemys; i++)
		{
			ignPos[i].ignorPosX = 0;
			ignPos[i].ignorPosY = 0;
		}
	}

	if (enemysList != NULL & ignPos != NULL)
	{
		for (int i = 0; i < countEnemys; i++)
		{
			enemysList[i].isKill = false;
			enemysList[i].texEnemy = InitTexturePng(rend, pathPng);
			enemysList[i].destEnemy = InitDest(enemysList[i].texEnemy);

			// высота и ширина объекта
			enemysList[i].destEnemy.w /= scale_ENEMY_PNG;
			enemysList[i].destEnemy.h /= scale_ENEMY_PNG;
			// позиция по осям объекта

			enemysList[i].destEnemy.x = RandomPosition(enemysList[i].destEnemy.w, (width - enemysList[i].destEnemy.w));
			enemysList[i].destEnemy.y = RandomPosition(enemysList[i].destEnemy.h, (height - enemysList[i].destEnemy.h));
			enemysList[i].angle=RandomAngle();
		}
	}

	return enemysList;
}

int RandomPosition(int min, int max)
{
	int rezult;
	rezult = min + rand() % (max - min + 1);
	return rezult;
}

int RandomAngle()
{
	int rezult,angle=0;
	rezult = 0 + rand() % (3 - 0 + 1);

	switch (rezult)
	{
	case 0:
		angle = Up;
		break;
	case 1:
		angle = Left;
		break;
	case 2:
		angle = Down;
		break;
	case 3:
		angle = Right;
		break;

	default:
		break;
	}
	return angle;
}

void MoviEnemys(Enemys* enemysList, int countEnemys, SDL_Renderer* rend)
{
	for (int i = 0; i < countEnemys; i++)
	{
		switch (enemysList[i].angle )
		{
		case Up:
			enemysList[i].destEnemy.y -= SPEED_ENEMY;
			break;
		case Left:
			enemysList[i].destEnemy.x -= SPEED_ENEMY;
			break;
		case Down:
			enemysList[i].destEnemy.y += SPEED_ENEMY;
			break;
		case Right:
			enemysList[i].destEnemy.x += SPEED_ENEMY;
			break;
		default:
			break;
		}

		if (BoundaryX(&enemysList[i].destEnemy, WIN_WIDTH) | BoundaryY(&enemysList[i].destEnemy, WIN_HEIGHT))
		{
			switch (enemysList[i].angle)
			{
			case Up:
				enemysList[i].angle = Down;
				break;
			case Left:
				enemysList[i].angle = Right;
				break;
			case Down:
				enemysList[i].angle = Up;
				break;
			case Right:
				enemysList[i].angle = Left;
				break;
			default:
				break;
			}

		}

		if (!enemysList[i].isKill)
		{
			UpDateRenderTexturePng(enemysList[i].texEnemy, rend, enemysList[i].destEnemy, enemysList[i].angle);
		}
		
	}
}