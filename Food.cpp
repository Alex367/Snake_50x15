#include "Food.h"
Food::Food() : food_symbol('@')
{
	static int tmp_food = 0;
	if (tmp_food == 0){
		x_pos = 3;
	}
	else if (tmp_food == 1){
		x_pos = 25;
	}
	else x_pos = 30 + tmp_food;

	if (tmp_food == 0){
		y_pos = 12;
	}
	else if (tmp_food == 1){
		y_pos = 5;
	}
	else y_pos = 10;

	COORD position = { x_pos, y_pos }; //position x , y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);

	std::cout << food_symbol;
	tmp_food++;
}

void Food::Get_pos_food(int &x, int &y){
	x = x_pos;
	y = y_pos;
}

void Food::Generate_food(int **&body_snake, int&snake_size){

	static int cnt_new_food = 0;
	// check the same point between food and body_snake
	while (true){
		x_pos = (rand() % MAX_INTERVAL_X) + 1;
		y_pos = (rand() % MAX_INTERVAL_Y) + 1;

		bool tmp = true;
		for (int i = 0, j = 0; i < snake_size; i++){
			if (x_pos == body_snake[i][j] && y_pos == body_snake[i][j + 1]){
				tmp = false;
				break;
			}
		}
		if (tmp)
			return;
	}
}

bool Check_same_food(int **&arr_f){

	for (int tmp_i = 0; tmp_i < MAX_FOOD - 1; tmp_i++){
		for (int i = tmp_i + 1; i < MAX_FOOD; i++){
			if (arr_f[tmp_i][0] == arr_f[i][0] && arr_f[tmp_i][1] == arr_f[i][1])
				return false;
		}
	}

	for (int i = 0, j = 0; i < MAX_FOOD; i++){
		COORD position = { arr_f[i][0], arr_f[i][1] };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		std::cout << "@";
	}
	return true;
}

Food::~Food()
{

}
