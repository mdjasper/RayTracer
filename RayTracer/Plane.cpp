#include "Plane.hpp"
#include <iostream>
#include "utils.h"

Plane::~Plane(){}

std::unique_ptr<HitRecord> Plane::intersect(Ray r) const
{
	r.o -= o;
    auto val = dot(r.d, n);
	if (val < .000001) return nullptr;
    float t = (-(dot(r.o, n) / dot(r.d, n)));
    
    Vector HitLocationNormal = n;
    return make_unique<HitRecord>(t, HitLocationNormal);
}

bool Plane::intersectP(Ray r) const {
    if(dot(n,o)==0){
        return false;
    }
    return true;
}

BBox Plane::getBoundingBox() const{
    BBox box;
    
    return box;
}
