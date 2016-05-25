#include "LineSegment.h"

using awcutil::Vector2f;

float cross2D(Vector2f p1, Vector2f p2)
{
	return p1.x*p2.y - p1.y*p2.x;
}

LineSegment::LineSegment()
{
}

LineSegment::LineSegment(awcutil::Vector2f _p1, awcutil::Vector2f _p2)
{
	p1 = _p1;
	p2 = _p2;
}

LineSegment::~LineSegment()
{
}
