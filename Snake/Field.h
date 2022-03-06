#pragma once
#include <iostream>
#include <vector>

class Snake;
class Fruit;

class Field
{
private:
	int width;
	int height;
	char border_symbol;

	std::vector<std::vector<char>> field;

public:

	Field(int h = 20, int w = 20, char border = '#');

	void set_fruit_coordinates(Fruit &fruit);
	void set_snake_coordinates(Snake& snake);
	void update_inner_region();

	int get_width() const { return width; }
	int get_height() const { return height; }

	const std::vector<std::vector<char>>& get_field() const { return field; }

private:
	void set_horizontal_borders();
	void set_vertical_borders();
};

