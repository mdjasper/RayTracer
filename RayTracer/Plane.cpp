#include "Plane.hpp"

std::unique_ptr<HitRecord> Plane::intersect(Ray r) const
{
	r.o -= o;
	if (dot(r.d, n) < 0.0000001) return nullptr;
	return std::make_unique<HitRecord>(- (dot(r.o, n) / dot(r.d, n)));
}