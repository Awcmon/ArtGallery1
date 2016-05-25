#include "Polygon.h"

Polygon::Polygon()
{
}

Polygon::Polygon(std::vector<awcutil::Vector2f> _vertices)
{
	vertices = _vertices;
}

Polygon::~Polygon()
{
}
/*
void Polygon::draw(bool fill)
{
	for()
}
*/