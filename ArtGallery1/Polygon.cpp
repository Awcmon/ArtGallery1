#include "Polygon.h"

using std::vector;

Polygon::Polygon()
{
}

Polygon::Polygon(std::vector<awcutil::Vector2f> _vertices)
{
	vertices = _vertices;
	segments = generateLineSegments();
}

Polygon::~Polygon()
{
}

std::vector<LineSegment> Polygon::generateLineSegments()
{
	vector<LineSegment> ret;
	for (int i = 0; i < (int)vertices.size(); i++)
	{
		ret.push_back(LineSegment(vertices[i], vertices[(i + 1) % vertices.size()]));
	}
	return ret;
}
