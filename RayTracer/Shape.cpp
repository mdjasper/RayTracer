#include "Shape.hpp"
#include <iostream>
//#include <cmath>

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
	if (!::intersect(r, getBoundingBox())) return nullptr;
	auto i = intersect(r);
	if (i){
		//check lighting
		auto intersectPoint = r.o + r.d * i->t;
		//For each light
        Point lightLocation {100, 300, 100}; //TODO get this from scene
        
		Vector lightDirection = lightLocation - intersectPoint;
        Vector normalizedLightDirection = normalize(lightDirection);
		//create a new ray from the intersect point to the light
        Ray l{intersectPoint, normalizedLightDirection};
        //if the camera->shape ray also reaches the light source:
        //to create shadows
        //if(hitP(l,Scene)){
        //}
		float red, green, blue; //TODO get matieral color info
        red = 255;
        green = 0;
        blue = 0;
    
        float baseColorValue = dot(normalizedLightDirection, l.d + i->normal);
        
        if(baseColorValue > 1){
//            std::cout << baseColorValue << "\n";
        }
        
//        std::cout << baseColorValue << "\n";
        
//        baseColorValue = dot(l, i->n);
        
        i->r = red * baseColorValue;
        i->g = green * baseColorValue;
        i->b = blue * baseColorValue;
        
	}
	return i;
	
}
