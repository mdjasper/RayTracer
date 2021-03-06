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
    Triangle(Point a, Point b, Point c, Color color) :a(a), b(b), c(c), color(color), isGlass(false){}
    Triangle(Point a, Point b, Point c, Color color, bool isGlass) :a(a), b(b), c(c), color(color), isGlass(isGlass){}
    virtual ~Triangle();
    BBox getBoundingBox() const override;
private:
    std::unique_ptr<HitRecord> intersect(Ray) const override;
    bool intersectP(Ray) const override;
    Point a, b, c;
    Color color;
    bool isGlass;
};

#endif /* Triangle_hpp */
