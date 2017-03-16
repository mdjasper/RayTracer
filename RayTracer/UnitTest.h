//
//  UnitTest.h
//  RayTracer
//
//  Created by Michael Jasper on 3/14/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#ifndef UnitTest_h
#define UnitTest_h

#include "Sphere.h"
#include "Triangle.hpp"

bool SphereTest(){
    
    Sphere *ball = new Sphere({0,0,0}, 9, blue);
    Ray r = Ray{Point{0,0,0}, Vector{1,1,1}};
    auto hit = ball->hit(r);
    return true;
}

bool TriangleTest(){
    Triangle *tri = new Triangle({-3,-3,5}, {3,-3,5}, {0,3,5}, red);
    
    Ray r = Ray{Point{0,0,0}, Vector{0,0,1}};
    auto hit = tri->hit(r);
    
    auto box = tri->getBoundingBox();
    
    return true;
}


#endif /* UnitTest_h */
