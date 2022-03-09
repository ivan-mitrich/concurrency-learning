#include "Car.h"

Car::Car(int h, int w, int speed) : RoadObject(h, w, speed), direction(MoveDirection::STOP)
{

}

void Car::process_input(int key)
{	
	switch (key)
	{
	case 'a':
		direction = MoveDirection::LEFT;
		break;
	case 'd':
		direction = MoveDirection::RIGHT;
		break;
	case 'w':
		direction = MoveDirection::FORWARD;
		break;
	case 's':
		direction = MoveDirection::BACKWARD;
		break;
	}
}

void Car::move()
{
	switch (direction)
	{
	case MoveDirection::LEFT:
		move_left();
		break;
	case MoveDirection::RIGHT:
		move_right();
		break;
	case MoveDirection::FORWARD:
		move_forward();
		break;
	case MoveDirection::BACKWARD:
		move_backward();
		break;
	case MoveDirection::STOP:
		break;
	}
	direction = MoveDirection::STOP;
}
