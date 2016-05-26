#include "Trace.h"

using std::vector;
using awcutil::Vector2f;

float cross2D(Vector2f p1, Vector2f p2)
{
	return p1.x*p2.y - p1.y*p2.x;
}

Trace::Trace()
{
}

Trace::Trace(awcutil::Vector2f _start, awcutil::Vector2f _endpos, Polygon poly)
{
	start = _start;
	endpos = _endpos;

	Vector2f p = start;
	Vector2f r = endpos - start;
	for (int j = 0; j < (int)poly.segments.size(); j++)
	{
		Vector2f q = poly.segments[j].p1;
		Vector2f s = poly.segments[j].p2 - poly.segments[j].p1;
		float t = cross2D((q - p), s) / cross2D(r, s);
		float u = cross2D((q - p), r) / cross2D(r, s);
		if (cross2D(r, s) == 0.0f && cross2D((q - p), r) == 0.0f)
		{
			std::cout << "Collinear\n";
		}
		else if (cross2D(r, s) == 0.0f && cross2D((q - p), r) != 0.0f)
		{
			std::cout << "parallel and non-intersecting\n";
		}
		else if (cross2D(r, s) != 0.0f && (t > 0.0f && t <= 1.0f) && (u > 0.0f && u <= 1.0f))
		{
			hits.push_back(p+r*t);
		}
		else
		{
			std::cout << "not parallel and non-intersecting\n";
		}
	}
	std::sort(hits.begin(), hits.end(),
		[=](Vector2f & a, Vector2f & b) -> bool
		{
			return (a - start).length_sqr() < (b - start).length_sqr();
		}
	);
}

Trace::~Trace()
{
}
