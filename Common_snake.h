#pragma once
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include "Food.h"

struct Point{
	int x;
	int y;
};

enum direction{ LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };
const int MAX_SNAKE = 10;

class Common_snake
{
protected:
	char object_symbol; // *
	Point *head;
	Point *tail;
	int **newBody;
	Food *food_obj[MAX_FOOD];
public:
	Common_snake();
	void Set_cursor(int, int);
	~Common_snake();
};

