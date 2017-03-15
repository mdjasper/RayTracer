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
    BBox box;
    return box;
}

bool Triangle::intersectP(Ray r) const {
    
    // compute plane's normal
    Vector ab = b - a;
    Vector ac = c - a;
    // no need to normalize
    Vector N = cross(ab, ac);//ab.crossProduct(ac); // N
    //    N = normalize(N);
    float area2 = length(N); // N.length();
    
    // Step 1: finding P
    
    // check if ray and plane are parallel ?
    float NdotRayDirection = dot(N, r.d); //N.dotProduct(dir);
    if (std::fabs(NdotRayDirection) < EPSILON) // almost 0
        return false; // they are parallel so they don't intersect !
    
    // compute d parameter using equation 2
    float d = dot(N, a); //N.dotProduct(a);
    
    // compute t (equation 3)
    float t = dot(N, r.o) + d / NdotRayDirection; //(N.dotProduct(orig) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind
    
    // compute the intersection point using equation 1
    Point P = r.o + r.d * t;
    
    // Step 2: inside-outside test
    Vector C; // vector perpendicular to triangle's plane
    
    // edge 0
    Vector edge0 = b - a;
    Vector vp0 = P - a;
    C = cross(edge0, vp0); //edge0.crossProduct(vp0);
    if (dot(N, C) < 0) return false; // P is on the right side
    
    // edge 1
    Vector edge1 = c - b;
    Vector vp1 = P - b;
    C = cross(edge1, vp1); //edge1.crossProduct(vp1);
    if (dot(N, C) < 0)  return false; // P is on the right side
    
    // edge 2
    Vector edge2 = a - c;
    Vector vp2 = P - c;
    C = cross(edge2, vp2); //edge2.crossProduct(vp2);
    if (dot(N, C) < 0) return false; // P is on the right side;
    
    std::cout << t << std::endl;
    
    return true; // this ray hits the triangle
}

std::unique_ptr<HitRecord> Triangle::intersect(Ray r) const{
    
    
    // compute plane's normal
    Vector ab = b - a;
    Vector ac = c - a;
    // no need to normalize
    Vector N = cross(ab, ac);//ab.crossProduct(ac); // N
//    N = normalize(N);
    float area2 = length(N); // N.length();
    
    // Step 1: finding P
    
    // check if ray and plane are parallel ?
    float NdotRayDirection = dot(N, r.d); //N.dotProduct(dir);
    if (std::fabs(NdotRayDirection) < EPSILON) // almost 0
        return nullptr; // they are parallel so they don't intersect !
    
    // compute d parameter using equation 2
    float d = dot(N, a); //N.dotProduct(a);
    
    // compute t (equation 3)
    float t = dot(N, r.o) + d / NdotRayDirection; //(N.dotProduct(orig) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return nullptr; // the triangle is behind
    
    // compute the intersection point using equation 1
    Point P = r.o + r.d * t;
    
    // Step 2: inside-outside test
    Vector C; // vector perpendicular to triangle's plane
    
    // edge 0
    Vector edge0 = b - a;
    Vector vp0 = P - a;
    C = cross(edge0, vp0); //edge0.crossProduct(vp0);
    if (dot(N, C) < 0) return nullptr; // P is on the right side
    
    // edge 1
    Vector edge1 = c - b;
    Vector vp1 = P - b;
    C = cross(edge1, vp1); //edge1.crossProduct(vp1);
    if (dot(N, C) < 0)  return nullptr; // P is on the right side
    
    // edge 2
    Vector edge2 = a - c;
    Vector vp2 = P - c;
    C = cross(edge2, vp2); //edge2.crossProduct(vp2);
    if (dot(N, C) < 0) return nullptr; // P is on the right side;
    
//    std::cout << t << std::endl;
    
    return make_unique<HitRecord>(t, N, color); // this ray hits the triangle
    
    
}






