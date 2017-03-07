#ifndef PLANE_HPP
#define PLANE_HPP
#include "Shape.hpp"
#include "Constants.h"

class Plane : public Shape{
public:
	Plane(Point o, Vector n, Color c) :o(o), n(n), c(c){}
    virtual ~Plane();
    BBox getBoundingBox() const override;
private:
    bool intersectP(Ray) const override;
	std::unique_ptr<HitRecord> intersect(Ray) const override;

	Point o;
	Vector n;
    Color c;
};


#endif
