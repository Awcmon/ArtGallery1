#pragma once

#include <vector>
#include "LineSegment.h"
#include <math.h>

class Polygon
{
public:
	std::vector<awcutil::Vector2f> vertices;
	std::vector<LineSegment> segments;
	float boundingDiagLength;

	Polygon();
	Polygon(std::vector<awcutil::Vector2f> _vertices);
	~Polygon();

	std::vector<LineSegment> generateLineSegments();
};

