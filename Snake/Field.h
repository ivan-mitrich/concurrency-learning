#pragma once
#include <iostream>
#include <vector>

class Fruit;

class Field
{
private:
	int width;
	int height;
	char border_symbol;

	std::vector<std::vector<char>> field;

	std::ostream &out;

public:

	Field(std::ostream& o, int h = 20, int w = 20, char border = '#');

	void print();
	void set_fruit(Fruit &fruit);
private:
	void set_horizontal_borders();
	void set_vertical_borders();
};

