#pragma once
#include "Snake.h"

const int MAX_ENEMY = 2;
const int WIDTH = 50;
const int HEIGHT = 15;

class Field
{
private:
	Snake *ptr_snake;
public:
	Field();
	void Draw();
	~Field();
};

