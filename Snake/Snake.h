#pragma once
#include <vector>

struct Link {
	Link(int i = 0, int j = 0, char c = 'o') : x(i), y(j), symbol(c) {}
	
	int x;
	int y;
	char symbol;
};

class Snake
{
private:
	std::vector<Link> body;

public:
	Snake();

	void add_link();
	
	int get_head_x() const { return body[0].x; }
	int get_head_y() const { return body[0].y; }
};

