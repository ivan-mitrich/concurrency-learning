#include "RoadObject.h"
RoadObject::RoadObject(int h, int w, int speed, char symbol) : body(h, w, symbol), position_x(0), position_y(-h + 1), speed_y(speed)
{
	
}