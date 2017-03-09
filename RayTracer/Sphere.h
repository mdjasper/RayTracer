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
    Sphere(Point o, float r, Color c) :origin(o), radius(r), color(c){}
    virtual ~Sphere();
    BBox getBoundingBox() const override;
private:
    std::unique_ptr<HitRecord> intersect(Ray) const override;
    bool intersectP(Ray) const override;
    Point origin;
    float radius;
    Color color;
};


#endif /* Sphere_h */
