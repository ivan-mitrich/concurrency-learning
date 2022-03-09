#pragma once
#include <iostream>
#include <vector>

class Car;
class RoadObject;

class Field
{
private:
	int width;
	int height;
	char road_markings_symbol;
	char road_borders_symbol;

	std::vector<std::vector<char>> field;

public:

	Field(int h = 20, int w = 22, char road_marks_symbol = '|', char borders_symbol = '#');

	void update_road();

	int get_width() const { return width; }
	int get_height() const { return height; }

	void set_car_on_field(const Car& car);
	void set_obstacle_on_field(const RoadObject& obstacle);

	const std::vector<std::vector<char>>& get_field() const { return field; }

private:
	void set_road_markers();

	int calculate_adjusted_x_car_position(const Car& car);
	int calculate_adjusted_y_car_position(const Car& car);
};

