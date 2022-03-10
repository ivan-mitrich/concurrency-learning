#pragma once
#include <vector>

class RoadObjectBody
{
private:
	int height;
	int width;

	std::vector<std::vector<char>> body;

	char body_symbol;

public:
	RoadObjectBody(int h = 3, int w = 3, char symbol = 'o');

	const std::vector<std::vector<char>>& get_body() const { return body; }

	int get_height() const { return height; }
	int get_width() const { return width; }
};

