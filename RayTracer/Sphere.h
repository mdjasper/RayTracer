//
//  Sphere.h
//  RayTracer
//
//  Created by Michael Jasper on 2/17/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include "Shape.hpp"
#include "Constants.h"


class Sphere : public Shape
{
public:
    Sphere(Point o, float radius, Color c) :o(o), radius(radius), c(c){}
    virtual ~Sphere();
    BBox getBoundingBox() const override;
private:
    std::unique_ptr<HitRecord> intersect(Ray) const override;
    bool intersectP(Ray) const override;
    Point o;
    float radius;
    Color c;
};


#endif /* Sphere_h */
