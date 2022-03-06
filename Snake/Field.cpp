#include "Field.h"
#include "Fruit.h"
#include "Snake.h"

Field::Field(int h, int w, char border) : height(h), width(w), border_symbol(border)
{
	field.resize(height);
	for (auto& row : field)
		row.resize(width, ' ');
	set_horizontal_borders();
	set_vertical_borders();
}

void Field::set_fruit_coordinates(Fruit& fruit)
{
	fruit.calculate_coordinates(width - 1, height - 1);
	field[fruit.get_x()][fruit.get_y()] = fruit.get_symbol();
}

void Field::set_snake_coordinates(Snake& snake)
{
	std::vector<Link> snake_body = snake.get_body();
	for (const auto& link : snake_body)
		field[link.x][link.y] = link.symbol;
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
