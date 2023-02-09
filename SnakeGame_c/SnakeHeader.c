#include "SnakeHeader.h"

void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Selectlevel(void)
{
	printf("난이도를 선택하세요 : (1 2 3)");
	scanf("%c", &level);
}

void LoadMaze(char num)
{
	//1.경로설정
	char path[20] = "./Maze";
	strcat(path, &num);
	strcat(path, ".txt");

	//2.파일불러오기
	char str_tmp[50] = { 0 };
	FILE* f = fopen(path, "r");

	//3.미로저장
	for (int i = 0; i < MAP_SIZE; i++)
	{
		fgets(str_tmp, 50, f);
		char* ptr = strtok(str_tmp, "\t");
		
		for (int j = 0; j < MAP_SIZE; j++)
		{
			maze[i][j] = *ptr;
			ptr = strtok(NULL, "\t");
		}
	}
	fclose(f);
}

//void DrawMap(void)
//{
//	for (int i = 0; i < MAP_SIZE; i++)
//	{
//		for (int j = 0; j < MAP_SIZE; j++)
//		{
//			printf("%c", maze[i][j]);
//		}
//		printf("\n");
//	}
//}

void PrintMazeGame(void)
{
	while (1)
	{
		for (int i = 0; i < MAP_SIZE; i++)
		{
			GotoXY(XP, YP + i);
			//콘솔창에 미로 그리기

			for (int j = 0; j < MAP_SIZE; j++)
			{
				if (maze[i][j] == '1')
				{
					printf("■");
				}
				else if (maze[i][j] == 'y')
				{
					printf("★");
				}
				else if (maze[i][j] == '0')
				{
					printf("□");
				}
				else
				{
					printf("●");
				}
			}
			printf("\n");
		}
	}
}

void CursorView(char show)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}