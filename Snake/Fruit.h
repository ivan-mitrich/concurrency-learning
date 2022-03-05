#pragma once
#include <iostream>
class Fruit
{
private:

	int x;
	int y;
	char fruit_symbol;

public:
	Fruit(char symbol = 'F');

	void calculate_coordinates(int max_x_coord, int max_y_coord);
	int get_x() const { return x; }
	int get_y() const { return y; }
	char get_symbol() const { return fruit_symbol; }

private:
	int get_random_coordinate_in_range(int min, int max);
};

