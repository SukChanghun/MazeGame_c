#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
//�ܼ��� ��ġ�� �����Ҽ��ִ� �Լ�
#include <stdio.h>

#define MAP_SIZE 19

void GotoXY(int x, int y);
//�����ġ�� �����ϴ� �Լ�
void LoadMaze(char num);
//�� �ε�


char maze[MAP_SIZE][MAP_SIZE];

int main(void)
{
	char level;
	printf("���̵��� �����ϼ��� : (1 2 3)");
	scanf("%c", &level);
	LoadMaze(level);

	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
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
