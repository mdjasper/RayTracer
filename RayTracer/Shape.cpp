#include "Shape.hpp"

bool Shape::intersectP(Ray r) const
{
	return(intersect(r)!=nullptr);
}

Shape::~Shape(){}

bool Shape::hitP(Ray r)const
{
	//test bbox intersection
	if (!::intersect(r, getBoundingBox())) return false;
	return intersectP(r);
}

std::unique_ptr<HitRecord> Shape::hit(Ray r)const
{
	if (!::intersect(r, getBoundingBox())) return false;
	auto i = intersect(r);
	if (i)
	{
		//check lighting
		auto intersectPoint = r.o + r.d * i->t;
		//For each light
		Point lightLocation; //TODO get this from scene
		Vector lightDirection = lightLocation - intersectPoint;
		Ray l{intersectPoint, lightDirection};
		//if(hitP(l,Scene))
		float red, green, blue; //TODO get matieral color info
		i->r = dot(lightDirection, i->n) * red;
		i->g = dot(lightDirection, i->n) * green;
		i->b = dot(lightDirection, i->n) * blue;
	}
	return i;
	
}