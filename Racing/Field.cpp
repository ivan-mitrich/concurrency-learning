#include "Field.h"
#include "Car.h"

Field::Field(int h, int w, char road_marks_symbol, char borders_symbol) : height(h), width(w), road_markings_symbol(road_marks_symbol), road_borders_symbol(borders_symbol)
{
	field.resize(height, std::vector<char>(width, ' '));
	for (int i = 0; i < height; ++i)
	{
		field[i][0] = road_borders_symbol;
		field[i][width - 1] = road_borders_symbol;
	}
	//for (auto& row : field)
		//row.resize(width, ' ');
}

void Field::set_road_markers()
{
	static int function_call_counter = 0;
	int road_middle = width / 2;
	for (int i = 0; i < height; ++i)
	{
		if(i % 2 == function_call_counter % 2)
			field[i][road_middle] = road_markings_symbol;
	}
	++function_call_counter;
}

int Field::calculate_adjusted_x_car_position(const Car& car)
{
	int car_x = car.get_car_x_position();
	if (car_x < 1)
		return 1;
	else if (car_x > width - 1 - car.get_car_width())
		return width - 1 - car.get_car_width();
	else
		return car_x;
}

int Field::calculate_adjusted_y_car_position(const Car& car)
{
	int car_y = car.get_car_y_position();
	if (car_y < 0)
		return 0;
	else if (car_y > height - car.get_car_height())
		return height - car.get_car_height();
	else
		return car_y;
}

void Field::update_road()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 1; j < width-1; ++j)
		{
			field[i][j] = ' ';
		}
	}
	set_road_markers();
}

void Field::set_car_on_field(Car& car)
{
	auto car_body = car.get_car_body();
	int car_x = car.get_car_x_position();
	int car_y = car.get_car_y_position();
	int new_car_y = calculate_adjusted_y_car_position(car);
	int new_car_x = calculate_adjusted_x_car_position(car);

	for (size_t i = 0; i < car_body.size(); ++i)
	{
		for (size_t j = 0; j < car_body[i].size(); ++j)
		{
			int y_coordinate = new_car_y + i;
			int x_coordinate = new_car_x + j;
			field[y_coordinate][x_coordinate] = car_body[i][j];
		}
	}
}
