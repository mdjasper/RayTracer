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
    Triangle(Vector a, Vector b, Vector c, Color color) :a(a), b(b), c(c){}
    virtual ~Triangle();
    BBox getBoundingBox() const override;
private:
    std::unique_ptr<HitRecord> intersect(Ray) const override;
    Vector a, b, c;
    float triangle_intersection( const Vector   V1,  // Triangle vertices
                                 const Vector   V2,
                                 const Vector   V3,
                                 const Vector    O,  //Ray origin
                                 const Vector    D  //Ray direction
    ) const;
    Color color;
};

#endif /* Triangle_hpp */
