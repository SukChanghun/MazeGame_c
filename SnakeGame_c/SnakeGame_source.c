#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>//�ܼ��� ��ġ�� �����Ҽ��ִ� �Լ�
#include <stdio.h>

#define MAP_SIZE 19

//�ܼ� �߾ӿ� �̷θ� ����ϱ����� �⺻��ǥ�� ����
#define XP 40
#define YP 5

void GotoXY(int x, int y);//�����ġ�� �����ϴ� �Լ�
void Selectlevel(void);// ��������
void LoadMaze(char num);//�� ���̵� ���� �Լ�
void DrawMap(void);//�׽�Ʈ �ʱ׸����Լ�
void PrintMazeGame(void);//�� �׸����Լ�
void CursorView(char show);//Ŀ�� ���ֱ� �Լ�

char maze[MAP_SIZE][MAP_SIZE];//�� �迭
char level;//�ʳ��̵�


int main(void)
{
	CursorView(0);

	Selectlevel();
	LoadMaze(level);
	//DrawMap(); // �׽�Ʈ
	PrintMazeGame();

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
	while (1)
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


