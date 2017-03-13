//
//  Triangle.hpp
//  RayTracer
//
//  Created by Michael Jasper on 2/27/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "Shape.hpp"


class Triangle : public Shape{
public:
    Triangle(Vector a, Vector b, Vector c, Color color) :a(a), b(b), color(color){}
    virtual ~Triangle();
    BBox getBoundingBox() const override;
private:
    std::unique_ptr<HitRecord> intersect(Ray) const override;
    bool intersectP(Ray) const override;
    Vector a, b, c;
    Color color;
};

#endif /* Triangle_hpp */
