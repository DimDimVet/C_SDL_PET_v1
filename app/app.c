#include "app.h"

int main(int argc, char* argv[])
{
	printf("Start DZ15\n");
	SummPlayerScore = 0;

	MainUpDate();

	return 0;
}

void LogicScorePlayer(int score)
{
	SummPlayerScore += score;
}

int ScorePlayer()
{
	return SummPlayerScore;
}
