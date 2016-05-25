#pragma once

#include <awcutil.h>

class LineSegment
{
public:
	awcutil::Vector2f p1;
	awcutil::Vector2f p2;

	LineSegment();
	LineSegment(awcutil::Vector2f _p1, awcutil::Vector2f _p2);
	~LineSegment();
};
