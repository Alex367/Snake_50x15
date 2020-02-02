#pragma once
#include "Common_snake.h"

class Snake : private Common_snake
{
private:
	int direction_snake;
	int score;
	int snake_size;
	int** snake_body;
public:
	Snake();
	void Snake_start();
	void Change_direction();
	void Lunch_time();
	void Change_snake_size();
	void Check_accident();
	~Snake();
};

