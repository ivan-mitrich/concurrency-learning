#pragma once
#include "RoadObject.h"

enum class MoveDirection
{
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
	STOP
};

class Car : public RoadObject
{
private:
	MoveDirection direction;

public:
	Car(int h = 3, int w = 3, int speed = 1);

	void process_input(int key);

	void move() override;

private:
	void move_left() { --position_x; }
	void move_right() { ++position_x; }
	void move_forward() { --position_y; } //position -= speed_y;
	void move_backward() { ++position_y; } //position += speed_y;
};

