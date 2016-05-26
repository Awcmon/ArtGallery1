#include "ArtGallery.h"

#include <iostream>

using std::vector;
using awcutil::Vector2f;
using awcutil::angr_normalize;
using awcutil::angr_difference;

extern float cross2D(Vector2f p1, Vector2f p2);

/*
float angle_between(float n, float a, float b) 
{
	n = fmod((360.0f + fmod(n, 360.0f)) , 360.0f);
	a = fmod((3600000.0f + a) , 360.0f);
	b = fmod((3600000.0f + b) , 360.0f);

	if (a < b)
	{
		return a <= n && n <= b;
	}
	return a <= n || n <= b;
}
*/

bool is_angle_between(int target, int angle1, int angle2)
{
	// make the angle from angle1 to angle2 to be <= 180 degrees
	int rAngle = ((angle2 - angle1) % 360 + 360) % 360;
	if (rAngle >= 180)
		std::swap(angle1, angle2);

	// check if it passes through zero
	if (angle1 <= angle2)
		return target >= angle1 && target <= angle2;
	else
		return target >= angle1 || target <= angle2;
}

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
		Vector2f p = guard;
		Vector2f r = sorted[i] - guard;
		for (int j = 0; j < (int)enclosing.segments.size(); j++)
		{
			Vector2f q = enclosing.segments[j].p1;
			Vector2f s = enclosing.segments[j].p2 - enclosing.segments[j].p1;
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
			else if (cross2D(r, s) != 0.0f && (t > 0.0f && t < 1.0f) && (u > 0.0f && u < 1.0f))
			{
				std::cout << "Path to " << sorted[i] << " blocked by line segment " << enclosing.segments[j].p1 << " to " << enclosing.segments[j].p2 << "\n";
				blocked = true;
				break;
			}
			else
			{
				std::cout << "not parallel and non-intersecting\n";
			}
		}
		if (!blocked)
		{
			std::cout << "\n" << sorted[i] << "\n";
			//Find if it is just an edge, or if it's a dead end.
			int index = 0;
			for (int k = 0; k < (int)enclosing.vertices.size(); k++)
			{
				if (enclosing.vertices[k] == sorted[i])
				{
					std::cout << "index: " << k << "\n";
					index = k;
					break;
				}
			}
			Vector2f dir = sorted[i] - guard;
			Vector2f dirp = enclosing.vertices[(index - 1 + enclosing.vertices.size()) % enclosing.vertices.size()] - enclosing.vertices[index];
			Vector2f dirn = enclosing.vertices[(index + 1) % enclosing.vertices.size()] - enclosing.vertices[index];
			float ang = angr_normalize(dir.angle());
			float angp = angr_normalize(dirp.angle());
			float angn = angr_normalize(dirn.angle());
			if(is_angle_between(ang, angp, angn) || is_angle_between(angr_normalize(ang+M_PI), angp, angn))
			{
				verts.push_back(sorted[i]);
				std::cout << "wall\n";
				std::cout << awcutil::angr_difference(angp, ang) << "\n";
				std::cout << awcutil::angr_difference(angn, ang) << "\n";
				std::cout << enclosing.vertices[(index - 1 + enclosing.vertices.size()) % enclosing.vertices.size()] << "\n";
				std::cout << enclosing.vertices[(index + 1) % enclosing.vertices.size()] << "\n";
				std::cout << ang << "\n";
				std::cout << angp << "\n";
				std::cout << angn << "\n";
				std::cout << "\n";
			}
			else
			{
				verts.push_back(sorted[i]);
				std::cout << "edge\n";
				std::cout << awcutil::angr_difference(angp, ang) << "\n";
				std::cout << awcutil::angr_difference(angn, ang) << "\n";
				std::cout << enclosing.vertices[(index - 1 + enclosing.vertices.size()) % enclosing.vertices.size()] << "\n";
				std::cout << enclosing.vertices[(index + 1) % enclosing.vertices.size()] << "\n";
				std::cout << ang << "\n";
				std::cout << angp << "\n";
				std::cout << angn << "\n";
				std::cout << "\n";
			}
			
		}
	}
	return Polygon(verts);
}
