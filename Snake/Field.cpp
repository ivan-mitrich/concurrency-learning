#include "Field.h"

Field::Field(std::ostream& o, int h, int w, char c) : out(o), height(h), width(w), border_symbol(c)
{

}

void Field::print()
{
	print_horizontal_edge_border();

	out << "\n";

	for (int j = 0; j < height - 2; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			if (i == 0 || i == width - 1)
				out << border_symbol;
			else
				out << " ";
		}
		out << "\n";
	}

	print_horizontal_edge_border();
}

void Field::print_horizontal_edge_border()
{
	for (int i = 0; i < width; ++i)
	{
		out << border_symbol;
	}
}
