#include "Snake.h"
Snake::Snake() : direction_snake(RIGHT), snake_size(4)
{
	head = new Point;
	head->x = 4;
	head->y = 6;
	tail = new Point;
	tail->x = 1;
	tail->y = 6;

	// initializate array
	snake_body = new int*[snake_size];
	for (int i = 0; i < snake_size; ++i)
		snake_body[i] = new int[2]; // coz x, y = 2

	// first snake's coordinate
	for (int i = 0, j = 0, coord = 1; i < snake_size; i++){
		snake_body[i][j] = coord;
		snake_body[i][j + 1] = 6;
		coord++;
	}

	// display snake
	for (int i = 0, j = 0; i < snake_size; i++){
		int tmp_x = snake_body[i][j];
		int tmp_y = snake_body[i][j + 1];
		Common_snake::Set_cursor(tmp_x, tmp_y);
		std::cout << "*";
	}

	//display food
	for (int i = 0; i < MAX_FOOD; i++)
		food_obj[i] = new Food;
}

void Snake::Snake_start(){
	static bool turn = false;
	static int prev_direction_snake = RIGHT;

	if (_kbhit()){
		direction_snake = _getch(); // change duraction
		turn = true;
	}

	if (prev_direction_snake == RIGHT && direction_snake == LEFT)
		direction_snake = RIGHT;
	else if (prev_direction_snake == LEFT && direction_snake == RIGHT)
		direction_snake = LEFT;
	else if (prev_direction_snake == UP && direction_snake == DOWN)
		direction_snake = UP;
	else if (prev_direction_snake == DOWN && direction_snake == UP)
		direction_snake = DOWN;

	switch (direction_snake)
	{
	case RIGHT:
		prev_direction_snake = RIGHT;
		head->x++;
		Change_direction();
		break;
	case LEFT:
		prev_direction_snake = LEFT;
		head->x--;
		Change_direction();
		break;
	case UP:
		prev_direction_snake = UP;
		head->y--;
		Change_direction();
		break;
	case DOWN:
		prev_direction_snake = DOWN;
		head->y++;
		Change_direction();
		break;
	}
}

void Snake::Change_direction(){

	Common_snake::Set_cursor(snake_body[0][0], snake_body[0][1]);
	std::cout << " ";

	for (int i = 0, j = 0; i < snake_size-1; i++){ // size - 1
		snake_body[i][j] = snake_body[i + 1][j];
		snake_body[i][j + 1] = snake_body[i + 1][j + 1];
	}

	// find last element in array
	snake_body[snake_size - 1][0] = head->x;
	snake_body[snake_size - 1][1] = head->y;

	Common_snake::Set_cursor(head->x, head->y);
	std::cout << "*";
	Check_accident();
	Lunch_time();
}

void Snake::Lunch_time(){
	int x_posit = 0;
	int y_posit = 0;
	static int eaten_food = 0; // tmp for generate food

	for (int i = 0; i < MAX_FOOD; i++){
		food_obj[i]->Get_pos_food(x_posit, y_posit);
		if (head->x == x_posit && head->y == y_posit){
			score++;
			snake_size++;
			Change_snake_size();
			eaten_food++;

			if (eaten_food == MAX_FOOD){
				eaten_food = 0;
				int res_same = false;

				while (res_same == false){
					int x_new_pos = 0;
					int y_new_pos = 0;

					// create array for food's coord.
					int **all_coord_food = new int*[MAX_FOOD];
					for (int i = 0; i < MAX_FOOD; i++)
						all_coord_food[i] = new int[2];

					for (int i = 0; i < MAX_FOOD; i++){
						// generate new food
						food_obj[i]->Generate_food(snake_body, snake_size);
						food_obj[i]->Get_pos_food(x_new_pos, y_new_pos);
						// add new points to array
						all_coord_food[i][0] = x_new_pos;
						all_coord_food[i][1] = y_new_pos;
					}
					// check points in array
					res_same = Check_same_food(all_coord_food);

					for (int i = 0; i < MAX_FOOD; i++)
						delete[] all_coord_food[i];
					delete[] all_coord_food;
				}
			}
		}
	}
}

void Snake::Change_snake_size(){
	// create new array
	newBody = new int*[snake_size]; // old size+1
	for (int i = 0; i < snake_size; i++)
		newBody[i] = new int[2];

	// copy values
	for (int z = 0, p = 0; z < snake_size-1; z++){
		newBody[z][p] = snake_body[z][p];
		newBody[z][p + 1] = snake_body[z][p + 1];
		p = 0;
	}
	// change head's position
	switch (direction_snake)
	{
	case RIGHT:
		head->x++;
		break;
	case LEFT:
		head->x--;
		break;
	case UP:
		head->y--;
		break;
	case DOWN:
		head->y++;
		break;
	}

	// add new value
	newBody[snake_size - 1][0] = head->x;
	newBody[snake_size - 1][1] = head->y;

	Common_snake::Set_cursor(head->x, head->y);
	std::cout << "*";

	// delete old array
	for (int i = 0; i < snake_size-1; i++)
		delete[] snake_body[i];
	delete[] snake_body;

	// change pointer
	snake_body = newBody;
}

void Snake::Check_accident(){
	// Check border
	if (head->x == 0 || head->y == 0 || head->x == 49 || head->y == 14){
		std::cout << "Game over";
		Sleep(1000);
		exit(0);
	}

	// Check kill yourself
	for (int i = 0, j = 0; i < snake_size-1; i++){
		if (head->x == snake_body[i][j] && head->y == snake_body[i][j + 1]){
			std::cout << "Game over";
			Sleep(1000);
			exit(0);
		}
	}
}

Snake::~Snake()
{
	for (int i = 0; i < snake_size; ++i) {
		delete[] snake_body[i];
	}
	delete[] snake_body;

	for (int i = 0; i < MAX_FOOD; i++)
		delete food_obj[i];

	for (int i = 0; i < snake_size; ++i) {
		delete[] newBody[i];
	}
	delete[] newBody;
}