#include <iostream>
#include "Field.h"
#include "Fruit.h"
#include "Snake.h"

int main() {
	Fruit fruit;
	Snake snake;
	Field field(std::cout);
	field.draw_fruit(fruit);
	field.draw_snake(snake);
	field.print();
	return 0;
}