#include "Field.h"
Field::Field()
{
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1)
				std::cout << "*";
			else std::cout << " ";
		}
		std::cout << "\n";
	}

	ptr_snake = new Snake();
}

void Field::Draw(){
	ptr_snake->Snake_start();
}

Field::~Field()
{
	delete ptr_snake;
}
