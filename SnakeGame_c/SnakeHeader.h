#pragma once
//SnakeHeader.h
#ifndef SnakeHeader
#define SnakeHeader

	#define _CRT_SECURE_NO_WARNINGS
	#include <Windows.h>
	#include <stdio.h>
	#include <conio.h>
	#include <time.h>

	#define MAP_SIZE 19
	#define XP 40
	#define YP 5
	#define LEFT 75
	#define RIGHT 77
	#define UP 72
	#define DOWN 80
	#define ARROW 224


	void GotoXY(int x, int y);
	void Selectlevel();
	void LoadMaze(char num);
	//void DrawMap(void);
	void PrintMazeGame();
	void CursorView(char show);
	//void MoveMaze_test();
	void MoveMaze(int* row, int* col);
	int IsBlock(int i, int j);
	int IsFinish(int i, int j);
	void Complete();

	char maze[MAP_SIZE][MAP_SIZE];
	char level;
	int row, col;
	clock_t start, end;
	float res;

#endif // !SnakeHeader.h