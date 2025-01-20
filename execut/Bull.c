#include "Bull.h"

void MoviBull(Bull* bull, SDL_Renderer* rend, SDL_Rect parentDest, int angle, int offset)
{
	SDL_Texture* texBull;
	SDL_Rect destBull;
	int isStop = 0;
	int countMax = bull->count;

	SDL_Texture* texFire;
	SDL_Rect destFire;

	if (bull->count != 0)
	{
		texBull = bull->texBull;
		destBull = bull->destBull;
		parentDest = bull->parentDest;
		angle = bull->angle;
		texFire = bull->texFire;
		destFire = bull->destFire;
	}
	else
	{
		texBull = InitTexturePng(rend, bull->pathBULLPNG);
		destBull = InitDest(texBull);

		texFire = InitTexturePng(rend, bull->pathFIREPNG);
		destFire = InitDest(texFire);
	}


	destBull.w /= 1;
	destBull.h /= 1;

	destBull.x = (parentDest.x + (parentDest.w / 2) - (destBull.w / 2));
	destBull.y = (parentDest.y + (parentDest.h / 2) - (destBull.h / 2));
	//
	isStop = BoundaryY(&destBull, bull->limitHeight) | BoundaryX(&destBull, bull->limitWidth);

	destFire.w /= 1;
	destFire.h /= 1;

	destFire.x = (destBull.x + (destBull.w / 2) - (destFire.w / 2));
	destFire.y = (destBull.y + (destBull.h / 2) - (destFire.h / 2));

	switch (angle)
	{
	case Up:
		destBull.y = destBull.y - offset;
		break;
	case Left:
		destBull.x = destBull.x - offset;;
		break;
	case Down:
		destBull.y = destBull.y + offset;
		break;
	case Right:
		destBull.x = destBull.x + offset;
		break;

	default:
		break;
	}

	bull->count++;

	if (isStop)
	{
		if (bull->count > (delay_FIRE))
		{
			bull->count = 0;
			bull->isRun = false;
			isStop = false;
		}
		else
		{
			texFire = bull->texFire;
			destFire = bull->destFire;
			isStop = true;
			UpDateRenderTexturePng(texFire, rend, destFire, angle);
		}
	}
	else
	{
		bull->count = 1;
		bull->texBull = texBull;
		bull->destBull = destBull;
		bull->parentDest.x = destBull.x++;
		bull->parentDest.y = destBull.y++;
		bull->parentDest.w = destBull.w;
		bull->parentDest.h = destBull.h;
		bull->angle = angle;

		bull->texFire = texFire;
		bull->destFire = destFire;

		UpDateRenderTexturePng(texBull, rend, destBull, angle);
	}
}

Bull* InitBulls(int count,char* pathBULLPNG,char* pathFIREPNG,int limitHeight,int limitWidth)
{
	Bull* enemyBulls;
	enemyBulls = malloc(count * sizeof(Bull));

	if (enemyBulls != NULL)
	{
		for (int i = 0; i < count; i++)
		{
			enemyBulls[i].isRun = false;
			enemyBulls[i].count = 0;
			enemyBulls[i].pathBULLPNG = pathBULLPNG;
			enemyBulls[i].pathFIREPNG = pathFIREPNG;
			enemyBulls[i].limitHeight = limitHeight;
			enemyBulls[i].limitWidth = limitWidth;
		}
	}

	return enemyBulls;
}