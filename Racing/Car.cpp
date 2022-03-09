#include "Car.h"

Car::Car(int h, int w, char symbol) : body(h, w, symbol), position_x(0), position_y(-h + 1)
{

}

void Car::process_input(int key)
{
	switch (key)
	{
	case 'a':
		move_left();
		break;
	case 'd':
		move_right();
		break;
	case 'w':
		move_forward();
		break;
	case 's':
		move_backward();
		break;
	}
}
