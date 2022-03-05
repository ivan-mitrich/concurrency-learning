#include "Field.h"
#include "Fruit.h"

Field::Field(std::ostream& o, int h, int w, char border) : out(o), height(h), width(w), border_symbol(border)
{
	field.resize(height);
	for (auto& row : field)
		row.resize(width, ' ');
	set_horizontal_borders();
	set_vertical_borders();
}

void Field::print()
{
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			out << field[i][j];
		}
		out << "\n";
	}
}

void Field::set_fruit(Fruit& fruit)
{
	fruit.calculate_coordinates(width - 1, height - 1);
	field[fruit.get_x()][fruit.get_y()] = fruit.get_symbol();
}

void Field::set_horizontal_borders()
{
	for (int i = 0; i < width; ++i)
	{
		field[i][0] = '#';
		field[i][height - 1] = '#';
	}
}

void Field::set_vertical_borders()
{
	for (int j = 0; j < height; ++j)
	{
		field[0][j] = '#';
		field[width - 1][j] = '#';
	}
}
