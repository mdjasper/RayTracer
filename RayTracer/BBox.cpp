#include "BBox.hpp"
#include <algorithm>

bool intersect(Ray r, BBox box)
{
	
    // adapted from http://gamedev.stackexchange.com/a/103714/16945
    
    float t[10];
    t[1] = (box.x.min - r.o.x)/r.d.x;
    t[2] = (box.x.max - r.o.x)/r.d.x;
    t[3] = (box.y.min - r.o.y)/r.d.y;
    t[4] = (box.y.max - r.o.y)/r.d.y;
    t[5] = (box.z.min - r.o.z)/r.d.z;
    t[6] = (box.z.max - r.o.z)/r.d.z;
    t[7] = fmax(fmax(fmin(t[1], t[2]), fmin(t[3], t[4])), fmin(t[5], t[6]));
    t[8] = fmin(fmin(fmax(t[1], t[2]), fmax(t[3], t[4])), fmax(t[5], t[6]));
    t[9] = (t[8] < 0 || t[7] > t[8]) ? false : t[7];
//    return t[9];
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
    BBox result;// = *new BBox();
	result.x = union_(a.x, b.x);
	result.y = union_(a.y, b.y);
	result.z = union_(a.z, b.z);
	return result;
}
