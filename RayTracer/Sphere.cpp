//
//  Sphere.cpp
//  RayTracer
//
//  Created by Michael Jasper on 2/17/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#include <stdio.h>
#include "Sphere.h"
#include "utils.h"
#include <math.h>
#include <iostream>

#define EPSILON  0.2

Sphere::~Sphere(){
//    std::cout << "sphere delete called" << std::endl;
}

BBox Sphere::getBoundingBox() const{
    
    Extent x,y,z;
    
    x.min = origin.x - radius;
    x.max = origin.x + radius;
    
    y.min = origin.y - radius;
    y.max = origin.y + radius;
    
    z.min = origin.z - radius;
    z.max = origin.z + radius;
    
    BBox box;
    
    box.x = x;
    box.y = y;
    box.z = z;
    
    return box;
};

bool Sphere::intersectP(Ray r) const {
    r.d = normalize(r.d);
    Vector w = r.o - origin;
    float A = dot(r.d, r.d);
    float B = 2 * dot(w, r.d);
    float C = dot(w,w) - (radius*radius);
    float D = (B*B) - (4.0f * A * C);
    
    if(D < EPSILON) return false;
    
    float t = (-B + sqrt(D))/(2.0f*A);
    
    if(t < EPSILON) return false;
    
    return t > 0;
    
}


std::unique_ptr<HitRecord> Sphere::intersect(Ray r) const
{
    r.d = normalize(r.d);
//    std::cout << r.d.x << " " << r.d.y << " " << r.d.z << std::endl;
    Vector w = r.o - origin;
    float A = dot(r.d, r.d);
    float B = 2 * dot(w, r.d);
    float C = dot(w,w) - (radius*radius);
    float D = (B*B) - (4.0f * A * C);
    
    
    if(D < 0.0f) return nullptr;
    
        
    //an intersection
    //solve pathagorean theorm to find intersection
    float t = (-B + sqrt(D))/(2.0f*A);
    
    if(t< EPSILON) return nullptr;
    
    //point of the intersection
    Point PHit = r.o + (r.d * t);
    //normal of the intersection
    Vector NHit = normalize(PHit - origin);

    return make_unique<HitRecord>(t, NHit, color);
}
