#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>//콘솔의 위치를 지정할수있는 함수
#include <stdio.h>
#include <conio.h>//콘솔 입출력 함수

#define MAP_SIZE 19

//콘솔 중앙에 미로를 출력하기위해 기본좌표값 설정
#define XP 40
#define YP 5

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ARROW 224

void GotoXY(int x, int y);//출력위치를 변경하는 함수
void Selectlevel();// 레벨설정
void LoadMaze(char num);//맵 난이도 설정 함수
void DrawMap();//테스트 맵그리기함수
void PrintMazeGame();//맵 그리기함수
void CursorView(char show);//커서 없애기 함수
void MoveMaze_test();//키 입력을 받는함수
void MoveMaze(int* row, int* col);//움직이기함수
int IsBlock(int i, int j);//주어진 좌표가 막힌곳, 혹은 도착지인지 판단함수
int IsFinish(int i, int j);//주아전 좌표가 도착지인지 판단함수

char maze[MAP_SIZE][MAP_SIZE];//맵 배열
char level;//맵난이도
int row, col;//플레이어 시작위치 좌표


int main(void)
{
	row = 2, col = 1;

	CursorView(0);

	GotoXY(XP, YP - 3);
	printf("미로찾기게임\n");
	Selectlevel();
	LoadMaze(level);
	//DrawMap(); // 테스트

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
	//COORD라는 구조체는 헤더파일에 선언되어있는 x,y값을 저장
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	//콘솔의 핸들값과 좌푯값을 받아서 해당위치로 콘솔 커서를 이동시킨다.
	//콘솔ID를 구하는 함수 (STD_OUTPUT_HANDLE), Pos 로 리턴받을수있음
}

void Selectlevel(void)
{

	GotoXY(XP, YP - 2);
	printf("난이도를 선택하세요 : (1 2 3)");
	scanf("%c", &level);
}

void LoadMaze(char num)
{
	//1.경로설정
	char path[20] = "./Maze";
	strcat(path, &num);
	strcat(path, ".txt");
	//strcat : 난이도 변수, 확장자를 합쳐준다.
	//path는 num이 1일때 ./Maze1.txt라는 값을 가지게됨

	//2.파일불러오기
	char str_tmp[50] = { 0 };
	FILE* f = fopen(path, "r");
	//fopen 함수 : 파일 포인터를 리턴받음

	//3.미로저장
	for (int i = 0; i < MAP_SIZE; i++)
	//첫번째 반복문의 내부에서 fgets로 한줄의 데이터를가져온다
	//다음 strtok함수를 이용해 탭으로 문자열을 분리한뒤, 미로에 저장한다.
	{
		fgets(str_tmp, 50, f);
		//fgets : gets_s함수와 비슷함
		//최대 크기가 '50'이하인 문자를 'f'로부터 읽어서, str_cmp에 저장한다.

		char* ptr = strtok(str_tmp, "\t");
		//char*strtok(char *string, char const*delimiter)
		//strtok : 문자열 string을 delimiter를 기준으로 잘라서 반환한다.
		//			string에 NULL을 넣고 실행하면, 이전에 자르고 남은 문자열을 다시
		//			delimiter로 잘라서 반환해준다.

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

void CursorView(char show)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	//CONSOLE_CURSOR_INFO 구조체를 생성
	//해당 구조체는 커서의 두께를 의미하는 dwSize와 커서의 노출 여부를 결정하는
	//bVisible 커서의 노출 여부를 결정하는 bVisible 두 개를 멤버 변수로 갖는답니다
	
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	//해당 변수는 True, False의 의미를 갖는 1, 0이 될 예정이니, bVisible의 값으로 설정

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
	//SetConsoleCursorInfo는 "콘솔의 핸들 값" 과 "콘솔 커서 정보"를 받아,
	//해당 콘솔의 설정을 변경하는 함수에요.
}

void MoveMaze_test(void) //의사코드로 작성
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
					printf("위");
					break;

				case DOWN:
					printf("아래");
					break;

				case LEFT:
					printf("왼쪽");
					break;

				case RIGHT:
					printf("오른쪽");
					break;
				}
			}
		}
	}
}

void MoveMaze(int* row, int* col) //의사코드로 작성
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
						//*row-1인이유 바로이동하고자 하는 좌표가 한칸 위의 좌표이기 때문에
					{
						maze[*row][*col] = '0'; //미로의 *(x), *(y)를 길로 변경
						maze[*row - 1][*col] = 'x'; //미로의 *(x), *(y-1)를 플레이어로 변경
						*row -= 1; //*(y)를 *(y)-1로 변경
					}
					else if(IsFinish(*row-1,*col)) //위쪽이 도착지라면?
					{
						exit(0);
						//임시로 강제종료
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

