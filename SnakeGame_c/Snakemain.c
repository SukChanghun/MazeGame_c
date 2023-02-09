#include "SnakeHeader.h"

int main(void)
{
	CursorView(0);

	Selectlevel();
	LoadMaze(level);
	PrintMazeGame();

	return 0;
}