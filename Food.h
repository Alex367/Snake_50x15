#pragma once
#include <Windows.h>
#include <iostream>

const int MAX_INTERVAL_X = 48;
const int MAX_INTERVAL_Y = 13;
const int MAX_FOOD = 3;

class Food
{
private:
	char food_symbol;
	int x_pos;
	int y_pos;
public:
	Food();
	void Get_pos_food(int&, int&);
	void Generate_food(int**&, int&);
	void Generate_point(int&, int**&, int&, const int&);
	friend bool Check_same_food(int**&);
	friend void Max_food_array_resize(int**&);
	~Food();
};

