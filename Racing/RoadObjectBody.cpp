#include "RoadObjectBody.h"

RoadObjectBody::RoadObjectBody(int h, int w, char symbol) : height(h), width(w), body_symbol(symbol)
{
	body.resize(height, std::vector<char>(width, body_symbol));
}
