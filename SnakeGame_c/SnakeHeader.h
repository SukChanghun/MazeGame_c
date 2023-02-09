#pragma once
//SnakeHeader.h
#ifndef SnakeHeader
#define SnakeHeader


	#define _CRT_SECURE_NO_WARNINGS
	#include <Windows.h>
	#include <stdio.h>

	#define MAP_SIZE 19
	#define XP 40
	#define YP 5


	void GotoXY(int x, int y);
	void Selectlevel(void);
	void LoadMaze(char num);
	//void DrawMap(void);
	void PrintMazeGame(void);
	void CursorView(char show);

	char maze[MAP_SIZE][MAP_SIZE];
	char level;

#endif // !SnakeHeader.h