#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>//�ܼ��� ��ġ�� �����Ҽ��ִ� �Լ�
#include <stdio.h>
#include <conio.h>//�ܼ� ����� �Լ�

#define MAP_SIZE 19

//�ܼ� �߾ӿ� �̷θ� ����ϱ����� �⺻��ǥ�� ����
#define XP 40
#define YP 5

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ARROW 224

void GotoXY(int x, int y);//�����ġ�� �����ϴ� �Լ�
void Selectlevel();// ��������
void LoadMaze(char num);//�� ���̵� ���� �Լ�
void DrawMap();//�׽�Ʈ �ʱ׸����Լ�
void PrintMazeGame();//�� �׸����Լ�
void CursorView(char show);//Ŀ�� ���ֱ� �Լ�
void MoveMaze_test();//Ű �Է��� �޴��Լ�
void MoveMaze(int* row, int* col);//�����̱��Լ�
int IsBlock(int i, int j);//�־��� ��ǥ�� ������, Ȥ�� ���������� �Ǵ��Լ�
int IsFinish(int i, int j);//�־��� ��ǥ�� ���������� �Ǵ��Լ�

char maze[MAP_SIZE][MAP_SIZE];//�� �迭
char level;//�ʳ��̵�
int row, col;//�÷��̾� ������ġ ��ǥ


int main(void)
{
	row = 2, col = 1;

	CursorView(0);

	GotoXY(XP, YP - 3);
	printf("�̷�ã�����\n");
	Selectlevel();
	LoadMaze(level);
	//DrawMap(); // �׽�Ʈ

	while (1)
	{
		PrintMazeGame();
		MoveMaze(&row, &col);
	}


	return 0;
}

void GotoXY(int x, int y)
{
	COORD Pos; 
	//COORD��� ����ü�� ������Ͽ� ����Ǿ��ִ� x,y���� ����
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	//�ܼ��� �ڵ鰪�� ��ǩ���� �޾Ƽ� �ش���ġ�� �ܼ� Ŀ���� �̵���Ų��.
	//�ܼ�ID�� ���ϴ� �Լ� (STD_OUTPUT_HANDLE), Pos �� ���Ϲ���������
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
	//strcat : ���̵� ����, Ȯ���ڸ� �����ش�.
	//path�� num�� 1�϶� ./Maze1.txt��� ���� �����Ե�

	//2.���Ϻҷ�����
	char str_tmp[50] = { 0 };
	FILE* f = fopen(path, "r");
	//fopen �Լ� : ���� �����͸� ���Ϲ���

	//3.�̷�����
	for (int i = 0; i < MAP_SIZE; i++)
	//ù��° �ݺ����� ���ο��� fgets�� ������ �����͸������´�
	//���� strtok�Լ��� �̿��� ������ ���ڿ��� �и��ѵ�, �̷ο� �����Ѵ�.
	{
		fgets(str_tmp, 50, f);
		//fgets : gets_s�Լ��� �����
		//�ִ� ũ�Ⱑ '50'������ ���ڸ� 'f'�κ��� �о, str_cmp�� �����Ѵ�.

		char* ptr = strtok(str_tmp, "\t");
		//char*strtok(char *string, char const*delimiter)
		//strtok : ���ڿ� string�� delimiter�� �������� �߶� ��ȯ�Ѵ�.
		//			string�� NULL�� �ְ� �����ϸ�, ������ �ڸ��� ���� ���ڿ��� �ٽ�
		//			delimiter�� �߶� ��ȯ���ش�.

		for (int j = 0; j < MAP_SIZE; j++)
		{
			maze[i][j] = *ptr;
			ptr = strtok(NULL, "\t");
		}
	}
	fclose(f);
}

void DrawMap(void)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

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
	//CONSOLE_CURSOR_INFO ����ü�� ����
	//�ش� ����ü�� Ŀ���� �β��� �ǹ��ϴ� dwSize�� Ŀ���� ���� ���θ� �����ϴ�
	//bVisible Ŀ���� ���� ���θ� �����ϴ� bVisible �� ���� ��� ������ ���´�ϴ�
	
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	//�ش� ������ True, False�� �ǹ̸� ���� 1, 0�� �� �����̴�, bVisible�� ������ ����

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
	//SetConsoleCursorInfo�� "�ܼ��� �ڵ� ��" �� "�ܼ� Ŀ�� ����"�� �޾�,
	//�ش� �ܼ��� ������ �����ϴ� �Լ�����.
}

void MoveMaze_test(void) //�ǻ��ڵ�� �ۼ�
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

void MoveMaze(int* row, int* col) //�ǻ��ڵ�� �ۼ�
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
					if (!(IsBlock(*row - 1, *col)))
						//*row-1������ �ٷ��̵��ϰ��� �ϴ� ��ǥ�� ��ĭ ���� ��ǥ�̱� ������
					{
						maze[*row][*col] = '0'; //�̷��� *(x), *(y)�� ��� ����
						maze[*row - 1][*col] = 'x'; //�̷��� *(x), *(y-1)�� �÷��̾�� ����
						*row -= 1; //*(y)�� *(y)-1�� ����
					}
					else if(IsFinish(*row-1,*col)) //������ ���������?
					{
						exit(0);
						//�ӽ÷� ��������
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

