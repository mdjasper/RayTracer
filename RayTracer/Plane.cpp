#include "Plane.hpp"
#include <iostream>
#include "utils.h"

Plane::~Plane(){}

bool Plane::intersectP(Ray r) const {
    if(dot(n,o)==0){
        return false;
    }
    return true;
}

std::unique_ptr<HitRecord> Plane::intersect(Ray r) const
{
//	r.o -= o;
    r.d = normalize(r.d);
    auto val = dot(r.d, n);
	if (val < .000001) return nullptr;
    float t = (-(dot(r.o, n) / dot(r.d, n)));
    
    std::cout << (r.o + r.d * t) << std::endl;
    
    return make_unique<HitRecord>(t, n, c);
    
}


BBox Plane::getBoundingBox() const{
    BBox box;
    
    return box;
}
