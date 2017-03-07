#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "BBox.hpp"
#include "Geometry.hpp"
#include <memory>

struct HitRecord
{
	HitRecord(float t) :t(t){}
	float t;
	Vector n;
	float r, g, b;
};

class Shape
{
public:
	virtual ~Shape() = 0;
	virtual BBox getBoundingBox() const = 0;
	bool hitP(Ray) const ;
	std::unique_ptr<HitRecord> hit(Ray) const;
private:
	virtual bool intersectP(Ray) const;
	virtual std::unique_ptr<HitRecord> intersect(Ray) const = 0;
};

#endif