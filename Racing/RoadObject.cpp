#include "RoadObject.h"
RoadObject::RoadObject(int h, int w, int speed) : body(h, w), position_x(0), position_y(-h + 1), speed_y(speed)
{
}