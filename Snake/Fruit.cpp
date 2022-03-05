#include "Fruit.h"
#include <random>
Fruit::Fruit(char symbol) : fruit_symbol(symbol), x(0), y(0)
{

}

void Fruit::calculate_coordinates(int max_x_coord, int max_y_coord)
{
	x = get_random_coordinate_in_range(1, max_x_coord - 1);
	y = get_random_coordinate_in_range(1, max_y_coord - 1);
}

int Fruit::get_random_coordinate_in_range(int min, int max)
{
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distribution(min, max);
	return distribution(generator);
}
