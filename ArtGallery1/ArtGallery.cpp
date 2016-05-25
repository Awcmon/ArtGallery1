#include "ArtGallery.h"

#include <iostream>

using std::vector;
using awcutil::Vector2f;

ArtGallery::ArtGallery()
{
}

ArtGallery::ArtGallery(Polygon _enclosing)
{
	enclosing = _enclosing;
}

ArtGallery::~ArtGallery()
{
}

Polygon ArtGallery::generateVisible(awcutil::Vector2f guard)
{
	vector<Vector2f> verts;
	vector<Vector2f> sorted = enclosing.vertices;
	std::sort(sorted.begin(), sorted.end(),
		[guard](Vector2f & a, Vector2f & b) -> bool
		{
			if ((a - guard).angle() != (b - guard).angle())
			{
				return (a - guard).angle() > (b - guard).angle();
			}
			else
			{
				return (a - guard).length_sqr() < (b - guard).length_sqr();
			}
		}
	);
	//trace a path to each sorted point
	for (int i = 0; i < (int)sorted.size(); i++)
	{
		//add if after checking all possibilities, the path does not collide with anything
		bool blocked = false;
		Vector2f E = sorted[i] - guard;
		Vector2f P = Vector2f(-E.y, E.x);
		for (int j = 0; j < (int)enclosing.segments.size(); j++)
		{
			Vector2f F = enclosing.segments[j].p2 - enclosing.segments[j].p1;
			float h = ((guard - enclosing.segments[j].p1) * P) / (F * P);
			if (h > -0.9f && h < 0.9f)
			{
				std::cout << "Path to " << sorted[i] << " blocked by line segment " << enclosing.segments[j].p1 << " to " << enclosing.segments[j].p2 << ", h = " << h << "\n";
				blocked = true;
				break;
			}
		}
		if (!blocked)
		{
			std::cout << sorted[i] << "\n";
			verts.push_back(sorted[i]);
		}
	}
	return Polygon(verts);
}
