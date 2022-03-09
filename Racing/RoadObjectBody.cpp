#include "RoadObjectBody.h"

RoadObjectBody::RoadObjectBody(int h, int w) : height(h), width(w)
{
	body.resize(height, std::vector<char>(width, 'o'));
}
