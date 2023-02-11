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
	GotoXY(XP, YP - 2);
	printf("���̵��� �����ϼ��� : (1 2 3)");
	scanf("%c", &level);
}

void LoadMaze(char num)
{
	//1.��μ���
	char path[20] = "./Maze";
	strcat(path, &num);
	strcat(path, ".txt");

	//2.���Ϻҷ�����
	char str_tmp[50] = { 0 };
	FILE* f = fopen(path, "r");

	//3.�̷�����
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
		for (int i = 0; i < MAP_SIZE; i++)
		{
			GotoXY(XP, YP + i);
			//�ܼ�â�� �̷� �׸���

			for (int j = 0; j < MAP_SIZE; j++)
			{
				if (maze[i][j] == '1')
				{
					printf("��");
				}
				else if (maze[i][j] == 'y')
				{
					printf("��");
				}
				else if (maze[i][j] == '0')
				{
					printf("��");
				}
				else
				{
					printf("��");
				}
			}
			printf("\n");
		}
}


void CursorView(char show)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void MoveMaze_test(void)
{
	while (1)
	{
		int nkey;

		if (_kbhit())
		{
			nkey = _getch();

			if (nkey == ARROW) //ARROW -> 224
			{
				nkey = _getch();

				switch (nkey)
				{
				case UP:
					printf("��");
					break;

				case DOWN:
					printf("�Ʒ�");
					break;

				case LEFT:
					printf("����");
					break;

				case RIGHT:
					printf("������");
					break;
				}
			}
		}
	}
}

void MoveMaze(int* row, int* col)
{
	int nkey;

	if (_kbhit())
	{
		nkey = _getch();

		if (nkey == ARROW)
		{
			nkey = _getch();
			switch (nkey)
			{
			case UP:
				if (!(IsBlock(*row - 1, *col)))
				{
					maze[*row][*col] = '0';
					maze[*row - 1][*col] = 'x';
					*row -= 1;
				}
				else if (IsFinish(*row - 1, *col))
				{
					exit(0);
				}
				break;

			case DOWN:
				if (!(IsBlock(*row + 1, *col)))
				{
					maze[*row][*col] = '0';
					maze[*row + 1][*col] = 'x';
					*row += 1;
				}
				else if (IsFinish(*row + 1, *col))
				{
					exit(0);
				}
				break;

			case LEFT:
				if (!(IsBlock(*row, *col - 1)))
				{
					maze[*row][*col] = '0';
					maze[*row][*col - 1] = 'x';
					*col -= 1;
				}
				else if (IsFinish(*row, *col - 1))
				{
					exit(0);
				}
				break;

			case RIGHT:
				if (!(IsBlock(*row, *col + 1)))
				{
					maze[*row][*col] = '0';
					maze[*row][*col + 1] = 'x';
					*col += 1;
				}
				else if (IsFinish(*row, *col + 1))
				{
					exit(0);
				}
				break;
			}
		}
	}
}

int IsBlock(int i, int j)
{
	if (maze[i][j] == '1' || maze[i][j] == 'y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsFinish(int i, int j)
{
	if (maze[i][j] == 'y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

