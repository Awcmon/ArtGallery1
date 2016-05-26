#pragma once

#include <vector>
#include <awcutil.h>
#include "Polygon.h"

class Trace
{
public:
	awcutil::Vector2f start;
	awcutil::Vector2f endpos;

	std::vector<awcutil::Vector2f> hits;

	Trace();
	Trace(awcutil::Vector2f _start, awcutil::Vector2f _endpos, Polygon poly);
	~Trace();
};

