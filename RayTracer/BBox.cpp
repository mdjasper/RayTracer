#include "BBox.hpp"
#include <algorithm>
bool intersect(Ray, BBox)
{
	//TODO this is MUCH to conservative, we should do the real test
	return true;
}

Extent union_(Extent a, Extent b)
{
	Extent result;
	result.min = std::min(a.min, b.min);
	result.max = std::max(a.max, b.max);
	return result;
}

BBox union_(BBox a, BBox b)
{
	BBox result;
	result.x = union_(a.x, b.x);
	result.y = union_(a.y, b.y);
	result.z = union_(a.z, b.z);
	return result;
}