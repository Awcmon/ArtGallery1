#pragma once

#include <vector>
#include "LineSegment.h"

class Polygon
{
public:
	std::vector<awcutil::Vector2f> vertices;
	std::vector<LineSegment> segments;

	Polygon();
	Polygon(std::vector<awcutil::Vector2f> _vertices);
	~Polygon();

	std::vector<LineSegment> generateLineSegments();
};

