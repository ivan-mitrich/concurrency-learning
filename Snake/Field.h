#pragma once
#include <iostream>

class Field
{
private:
	int width;
	int height;
	char border_symbol;

	std::ostream &out;

public:

	Field(std::ostream& o, int h = 20, int w = 20, char c = '#');

	void print();

private:
	void print_horizontal_edge_border();
};

