#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "BBox.hpp"
#include "Geometry.hpp"
#include "Constants.h"
#include <memory>

struct HitRecord{
	HitRecord(float t, Vector normal, Color c) :t(t), normal(normal), c(c){}
	float t;
	Vector normal;
	Color c;
};

class Shape{
public:
	virtual ~Shape() = 0;
	virtual BBox getBoundingBox() const = 0;
	bool hitP(Ray) const ;
	std::unique_ptr<HitRecord> hit(Ray) const;
private:
	virtual bool intersectP(Ray) const = 0;
	virtual std::unique_ptr<HitRecord> intersect(Ray) const = 0;
    Color color;
};

#endif
