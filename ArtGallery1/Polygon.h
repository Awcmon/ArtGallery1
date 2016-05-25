#pragma once

#include <awcutil.h>
#include <vector>

class Polygon
{
public:
	std::vector<awcutil::Vector2f> vertices;

	Polygon();
	Polygon(std::vector<awcutil::Vector2f> _vertices);
	~Polygon();

//	void draw(bool fill);
};

