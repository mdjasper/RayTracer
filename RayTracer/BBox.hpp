#ifndef BBOX_HPP
#define BBOX_HPP

#include "Geometry.hpp"
#include <limits>
//Axis Aligned bounding box

struct Extent
{
	Extent() :min(std::numeric_limits<float>::max()), max(std::numeric_limits<float>::min()){}
	float min, max;
};

struct BBox
{
	BBox() :x(), y(), z(){}
	Extent x, y, z;
};

Extent union_(Extent, Extent);
BBox union_(BBox, BBox);
bool intersect(Ray, BBox);


#endif