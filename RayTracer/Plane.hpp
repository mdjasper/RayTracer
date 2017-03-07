#ifndef PLANE_HPP
#define PLANE_HPP
#include "Shape.hpp"

class Plane : public Shape
{
public:
	Plane(Point o, Vector n) :o(o), n(n){}
	~Plane() = default;
	BBox getBoundingBox() const override;
private:
	std::unique_ptr<HitRecord> intersect(Ray) const override;

	Point o;
	Vector n;
};


#endif