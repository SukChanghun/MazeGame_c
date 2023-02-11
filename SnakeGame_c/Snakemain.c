#include "SnakeHeader.h"

int main(void)
{
	row = 2, col = 1;

	CursorView(0);

	GotoXY(XP, YP - 3);
	printf("미로찾기게임\n");
	Selectlevel();
	LoadMaze(level);

	while (1)
	{
		PrintMazeGame();
		MoveMaze(&row, &col);
	}

	return 0;
}