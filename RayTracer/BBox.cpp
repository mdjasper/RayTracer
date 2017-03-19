#include "BBox.hpp"
#include <algorithm>

bool intersect(Ray r, BBox box)
{
	
    //adapted from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
    
    
    float tmin = (box.x.min - r.o.x) / r.d.x;
    float tmax = (box.x.max - r.o.x) / r.d.x;
    
    if (tmin > tmax) std::swap(tmin, tmax);
    
    float tymin = (box.y.min - r.o.y) / r.d.y;
    float tymax = (box.y.max - r.o.y) / r.d.y;
    
    if (tymin > tymax) std::swap(tymin, tymax);
    
    if ((tmin > tymax) || (tymin > tmax))
        return false;
    
    if (tymin > tmin)
        tmin = tymin;
    
    if (tymax < tmax)
        tmax = tymax;
    
    float tzmin = (box.z.min - r.o.z) / r.d.z;
    float tzmax = (box.z.max - r.o.z) / r.d.z;
    
    if (tzmin > tzmax) std::swap(tzmin, tzmax);
    
    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    
    if (tzmin > tmin)
        tmin = tzmin;
    
    if (tzmax < tmax)
        tmax = tzmax;
    
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
