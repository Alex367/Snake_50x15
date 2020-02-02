#include "Common_snake.h"
Common_snake::Common_snake() : object_symbol('*')
{
}

void Common_snake::Set_cursor(int x, int y){
	COORD position = { x, y }; //position x , y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}

Common_snake::~Common_snake()
{
}
