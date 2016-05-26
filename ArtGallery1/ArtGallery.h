#pragma once

#include "Polygon.h"
#include "Trace.h"
#include <algorithm>
#include <functional>

class ArtGallery
{
public:
	Polygon enclosing;
	//std::vector<awcutil::Vector2f> guards;

	ArtGallery();
	ArtGallery(Polygon _enclosing);
	~ArtGallery();

	Polygon generateVisible(awcutil::Vector2f guard);
};

