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

Sphere::~Sphere(){
    std::cout << "sphere delete called" << std::endl;
}

BBox Sphere::getBoundingBox() const{
    BBox box;
    return box;
};

//std::unique_ptr<HitRecord> intersect(Ray r){
//    return nullptr;
//};

bool Sphere::intersectP(Ray r) const {
    return true;
}


std::unique_ptr<HitRecord> Sphere::intersect(Ray r) const
{
    r.d = normalize(r.d);
    Vector w = normalize(r.o - o);
    float A = dot(r.d, r.d);
    float B = 2 * dot(w, r.d);
    float C = dot(w,w) - (radius*radius);
    float D = (B*B) - (4.0f * A * C);
    
    
    if(D < 0.0f){
        //no intersections
        std::cout << "no intersections";
        return nullptr;
    } else {
        //an intersection
        //solve pathagorean theorm to find intersection
        float t = (-B + sqrt(D))/(2.0f*A);
        
        //point of the intersection
        Point PHit = r.o + (r.d * t);
        //normal of the intersection
        Vector NHit = normalize(PHit - o);
        std::cout << "Sphere D:" << D << "\t Sphere t: " << t << "\n";
        return make_unique<HitRecord>(t, NHit);
    }
}
