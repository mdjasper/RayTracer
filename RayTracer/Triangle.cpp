//
//  Triangle.cpp
//  RayTracer
//
//  Created by Michael Jasper on 2/27/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution

#include "Triangle.hpp"
#include "utils.h"
#include <iostream>

#define EPSILON 0.0001

Triangle::~Triangle(){}

BBox Triangle::getBoundingBox() const{
    
    Extent x,y,z;
    
    x.max = x.max > b.x ? x.max : b.x;
    x.max = x.max > c.x ? x.max : c.x;
    
    y.max = y.max > b.y ? y.max : b.y;
    y.max = y.max > c.y ? y.max : c.y;
    
    z.max = z.max > b.z ? z.max : b.z;
    z.max = z.max > c.z ? z.max : c.z;
    
    x.min = x.min < b.x ? x.min : b.x;
    x.min = x.min < c.x ? x.min : c.x;
    
    y.min = y.min < b.y ? y.min : b.y;
    y.min = y.min < c.y ? y.min : c.y;
    
    z.min = z.min < b.z ? z.min : b.z;
    z.min = z.min < c.z ? z.min : c.z;
    
    BBox box;
    box.x = x;
    box.y = y;
    box.z = z;
    
    return box;
}

bool Triangle::intersectP(Ray r) const {
    /*
     Möller-Trumbore algorithm
     https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
     */
    
    Vector v0v1 = c - a;
    Vector v0v2 = b - a;
    Vector pvec = cross(r.d, v0v2); //dir.crossProduct(v0v2);
    float det = dot(v0v1, pvec); //v0v1.dotProduct(pvec);
    
    if (fabs(det) < EPSILON) return false;
    
    float invDet = 1 / det;
    
    Vector tvec = r.o - a;
    float u = dot(tvec, pvec) * invDet; //tvec.dotProduct(pvec) * invDet;
    if (u < 0 || u > 1) return false;
    
    Vector qvec = cross(tvec, v0v1); //tvec.crossProduct(v0v1);
    float v = dot(r.d, qvec); //dir.dotProduct(qvec) * invDet;
    if (v < 0 || u + v > 1) return false;
    
    float t = dot(v0v2, qvec) * invDet; //v0v2.dotProduct(qvec) * invDet;
    
    return true; // this ray hits the triangle
}

std::unique_ptr<HitRecord> Triangle::intersect(Ray r) const{
    /*
     Möller-Trumbore algorithm
     https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
     */
    
    Vector v0v1 = c - a;
    Vector v0v2 = b - a;
    Vector pvec = cross(r.d, v0v2); //dir.crossProduct(v0v2);
    float det = dot(v0v1, pvec); //v0v1.dotProduct(pvec);

    if (fabs(det) < EPSILON) return nullptr;

    float invDet = 1 / det;
    
    Vector tvec = r.o - a;
    float u = dot(tvec, pvec) * invDet; //tvec.dotProduct(pvec) * invDet;
    if (u < 0 || u > 1) return nullptr;
    
    Vector qvec = cross(tvec, v0v1); //tvec.crossProduct(v0v1);
    float v = dot(r.d, qvec); //dir.dotProduct(qvec) * invDet;
    if (v < 0 || u + v > 1) return nullptr;
    
    float t = dot(v0v2, qvec) * invDet; //v0v2.dotProduct(qvec) * invDet;
    
    Vector normal = cross(v0v1, v0v2);
    
    return make_unique<HitRecord>(t, normal, color); // this ray hits the triangle
}






