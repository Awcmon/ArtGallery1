#pragma once

#include "Polygon.h"

class ArtGallery
{
public:
	Polygon enclosing;
	//std::vector<awcutil::Vector2f> guards;

	ArtGallery();
	~ArtGallery();

	Polygon generateVisible(awcutil::Vector2f guard);
};

