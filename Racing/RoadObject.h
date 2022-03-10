#pragma once
#include "RoadObjectBody.h"

class RoadObject
{
private:
	RoadObjectBody body;
	int speed_y;

protected:
	/*  
	*	Position of the top left point of the road object body in field coordinates.
	*	Top left point was chosen because of 2d array indexing.
	*/
	int position_x;
	int position_y;

public:
	RoadObject(int h = 3, int w = 3, int speed_y = 1, char symbol = 'o');

	const std::vector<std::vector<char>>& get_body() const { return body.get_body(); }
	int get_x_position() const { return position_x; }
	int get_y_position() const { return position_y; }
	int get_width() const { return body.get_width(); }
	int get_height() const { return body.get_height(); }

	void set_x_position(int x) { position_x = x; }
	void set_y_position(int y) { position_y = y; }

	virtual void move() { position_y += speed_y; }
};

