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
    
    auto box = ball->getBoundingBox();
    
    return true;
}

bool TriangleTest(){
    Triangle *tri = new Triangle({-3,-3,5}, {3,-3,5}, {0,3,5}, red);
    
    Ray r = Ray{Point{0,0,0}, Vector{0,0,1}};
    auto hit = tri->hit(r);
    
    auto box = tri->getBoundingBox();
    
    return true;
}

bool BvhTest(){
    Sphere *s = new Sphere({0,0,0}, 5, red);
    
    Sphere *s1 = new Sphere({-5,-5,-5}, 1, red);
    Sphere *s2 = new Sphere({-5,-5,-5}, 1, red);
    Sphere *s3 = new Sphere({-6,-6,-6}, 1, red);
    Sphere *s4 = new Sphere({-7,-7,-7}, 1, red);
    Sphere *s5 = new Sphere({-8,-8,-8}, 1, red);
    Sphere *s6 = new Sphere({-9,-9,-9}, 1, red);
    
    BVH *bvh = new BVH();
    bvh->addShape(std::unique_ptr<Shape>(s));
    bvh->addShape(std::unique_ptr<Shape>(s1));
    bvh->addShape(std::unique_ptr<Shape>(s2));
    bvh->addShape(std::unique_ptr<Shape>(s3));
    bvh->addShape(std::unique_ptr<Shape>(s4));
    bvh->addShape(std::unique_ptr<Shape>(s5));
    bvh->addShape(std::unique_ptr<Shape>(s6));
    bvh->balance();
    
    Ray r = Ray{Point{0,0,-10}, Vector{0,0,1}};
    
    auto hit = bvh->hit(r);
    return true;
    
}


#endif /* UnitTest_h */
