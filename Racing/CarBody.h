#pragma once
#include <vector>

class CarBody
{
private:
	int height;
	int width;

	char body_symbol;

	std::vector<std::vector<char>> body;

public:
	CarBody(int h = 8, int w = 8, char symbol = 'o');

	const std::vector<std::vector<char>>& get_car_body() const { return body; }

	int get_height() const { return height; }
	int get_width() const { return width; }
};

