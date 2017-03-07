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

Sphere::~Sphere(){}

BBox Sphere::getBoundingBox() const{
    BBox box;
    return box;
};

std::unique_ptr<HitRecord> intersect(Ray r){
    return nullptr;
};

//bool Sphere::intersectP(Ray r) const {
//    return true;
//}

/*
std::unique_ptr<HitRecord> Sphere::intersect(Ray r) const
{
    r.d = normalize(r.d);
    Vector w = normalize(r.o - o);
    float A = dot(r.d, r.d);
    float B = 2 * dot(w, r.d);
    float C = dot(w,w) - (radius*radius);
    float D = (B*B) - 4.0f * A * C;
    
    //solve pathagorean theorm to find intersection
    float t = (-B - sqrt(D))/(2.0f*A);
    
    //point of the intersection
    Point PHit = r.o + r.d * t;
    //normal of the intersection
    Vector NHit = normalize(PHit - o);
    
    
    
    if(D >= 0.0f){
        //no intersections
        return nullptr;
    } else {
        //an intersection
        std::cout << "Sphere D:" << D << "\t Sphere t: " << t << "\n";
        return make_unique<HitRecord>(t, NHit);
    }
}
*/

std::unique_ptr<HitRecord> Sphere::intersect(Ray ray) const {
    float phi;
    Point phit;
    
    // Compute quadratic sphere coefficients
    
    //x^2 + y^2 + z^2
    float A = (ray.d.x*ray.d.x) + (ray.d.y*ray.d.y) + (ray.d.z*ray.d.z);
    
    float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z);
    float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y +
    ray.o.z*ray.o.z - radius*radius;
    
    // Solve quadratic equation for _t_ values
    float t0, t1;
    bool isQuadratic = Quadratic(A, B, C, &t0, &t1);
    if (!isQuadratic){
        return nullptr;
    } else {
        std::cout << "hit sphere" << std::endl;
        return make_unique<HitRecord>(t0, Vector{1,1,1});
    }
}

/*
 quadratic from pbrt
 https://www.csie.ntu.edu.tw/~cyy/courses/rendering/pbrt-2.00/html/pbrt_8h_source.html#l00291
 */
inline bool Sphere::Quadratic(float A, float B, float C, float *t0, float *t1) const{
    // Find quadratic discriminant
    float discrim = B * B - 4.f * A * C;
    if (discrim <= 0.) return false;
    float rootDiscrim = sqrtf(discrim);
    
    // Compute quadratic _t_ values
    float q;
    if (B < 0) q = -.5f * (B - rootDiscrim);
    else       q = -.5f * (B + rootDiscrim);
    *t0 = q / A;
    *t1 = C / q;
    if (*t0 > *t1) std::swap(*t0, *t1);
    return true;
}
