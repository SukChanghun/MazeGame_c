#pragma once
//SnakeHeader.h
#ifndef SnakeHeader
#define SnakeHeader


	#define _CRT_SECURE_NO_WARNINGS
	#include <Windows.h>//�ܼ��� ��ġ�� �����Ҽ��ִ� �Լ�
	#include <stdio.h>

	#define MAP_SIZE 19

	void GotoXY(int x, int y);//�����ġ�� �����ϴ� �Լ�
	void Selectlevel(void);
	void LoadMaze(char num);//�� ���̵� ���� �Լ�
	void DrawMap(void);

	char maze[MAP_SIZE][MAP_SIZE];//�� �迭
	char level;//�ʳ��̵�

#endif // !SnakeHeader.h