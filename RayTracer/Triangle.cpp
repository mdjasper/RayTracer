//
//  Triangle.cpp
//  RayTracer
//
//  Created by Michael Jasper on 2/27/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#include "Triangle.hpp"
#include "utils.h"
#include <iostream>

#define EPSILON 0.000001

Triangle::~Triangle(){}

BBox Triangle::getBoundingBox() const{
    BBox box;
    return box;
}

bool Triangle::intersectP(Ray r) const {
    return true;
}

std::unique_ptr<HitRecord> Triangle::intersect(Ray r) const{
    
    
    //normalize ray direction vector, and convert ray origin to vector
    r.d = normalize(r.d);
    Vector O = {r.o.x, r.o.y, r.o.z};
    
    
    //Find vectors for two edges sharing a
    Vector e1 = b-a;
    Vector e2 = c-a;

    //if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
    Vector triNormal = cross(r.d, e2);
    
    std::cout << triNormal << std::endl;
    
    //Begin calculating determinant - also used to calculate u parameter
    float det = dot(e1, triNormal);
    
    //NOT CULLING
    if(det > -EPSILON && det < EPSILON){
        return nullptr;
    }
    
    float inv_det = 1.f/det;
    
    //calculate distance from a to ray origin
    Vector T = O - a;
    
    //Calculate u parameter and test bound
    float u = dot(T, triNormal);
    
//    std::cout << u << "\n";
    
    //The intersection lies outside of the triangle
    if(u < 0.f || u > 1.f){
//        std::cout << "tri not hit" << std::endl;
        return nullptr;
    }

    //Prepare to test v parameter
    Vector Q = cross(T, e1);
    
    //Calculate V parameter and test bound
    float v = dot(r.d, Q) * inv_det;
    
//    std::cout << v << "\n";
    
    if(v < 0.f || u + v  > 1.f) {
        return nullptr;
    }
    
    float t = dot(e2, Q) * inv_det;
    std::cout << t << "\n";
    
    if(t > EPSILON){
        std::cout << "Triangle Hit" << std::endl;
        return make_unique<HitRecord>(t, normalize(triNormal), color);
    }
    
    return nullptr;
     
    
    
}






