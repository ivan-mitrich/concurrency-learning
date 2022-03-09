#pragma once
#include <vector>
#include "CarBody.h"

class Car
{
private:
	CarBody body;

	/*  position of the top left point of the car body in field coordinates.
	*	Top left point was chosen because of 2d array indexing.	
	*/
	int position_x;
	int position_y;

	//int speed_y;
public:
	Car(int h = 2, int w = 2, char symbol = 'o');

	const std::vector<std::vector<char>>& get_car_body() const { return body.get_car_body(); }
	int get_car_x_position() const { return position_x; }
	int get_car_y_position() const { return position_y; }
	int get_car_width() const { return body.get_width(); }
	int get_car_height() const { return body.get_height(); }

	void set_car_x_position(int x) { position_x = x; }
	void set_car_y_position(int y) { position_y = y; }

	void process_input(int key);

private:
	void move_left() { --position_x; }
	void move_right() { ++position_x; }
	void move_forward() { --position_y; } //position -= speed_y;
	void move_backward() { ++position_y; } //position += speed_y;
};

