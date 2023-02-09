#pragma once
//SnakeHeader.h
#ifndef SnakeHeader
#define SnakeHeader


	#define _CRT_SECURE_NO_WARNINGS
	#include <Windows.h>//콘솔의 위치를 지정할수있는 함수
	#include <stdio.h>

	#define MAP_SIZE 19

	void GotoXY(int x, int y);//출력위치를 변경하는 함수
	void Selectlevel(void);
	void LoadMaze(char num);//맵 난이도 설정 함수
	void DrawMap(void);

	char maze[MAP_SIZE][MAP_SIZE];//맵 배열
	char level;//맵난이도

#endif // !SnakeHeader.h