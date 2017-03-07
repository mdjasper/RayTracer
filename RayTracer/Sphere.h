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
    inline bool Quadratic(float A, float B, float C, float *t0, float *t1) const;
    Point o;
    float radius;
    Color c;
};


#endif /* Sphere_h */
