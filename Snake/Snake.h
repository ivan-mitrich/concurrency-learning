#pragma once
#include <vector>

struct Link {
	Link(int i = 1, int j = 1, char c = 'o') : x(i), y(j), symbol(c) {}
	
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
	const std::vector<Link>& get_body() const { return body; }
	
	int get_head_x() const { return body[0].x; }
	int get_head_y() const { return body[0].y; }
};

