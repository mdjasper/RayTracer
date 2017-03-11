#include "Shape.hpp"
#include "ShapeList.hpp"
#include <iostream>
//#include <cmath>

bool Shape::intersectP(Ray r) const {
	return(intersect(r)!=nullptr);
}

Shape::~Shape(){}

bool Shape::hitP(Ray r)const {
	//test bbox intersection
	if (!::intersect(r, getBoundingBox())) return false;
	return intersectP(r);
}

std::unique_ptr<HitRecord> Shape::hit(Ray r)const {
	if (!::intersect(r, getBoundingBox())) return nullptr;
	auto i = intersect(r);
	if (i){
		//check lighting
		auto intersectPoint = r.o + r.d * i->t;
		//For each light
        
        
		//create a new ray from the intersect point to the light
        Point lightLocation = * new Point{100, 300, 100}; //TODO get this from scene
        Vector lightDirection = lightLocation - intersectPoint;
        Ray l = * new Ray{intersectPoint, lightDirection};
        
        //if the camera->shape ray also reaches the light source:
        //to create shadows
        if(r.o != lightLocation){
            auto lightHit = ShapeList::getInstance().hit(l);
            if(lightHit){
                //hit can see the light
                //              float baseColorValue = dot(normalize(r.d), normalize(l.d) + i->normal);
                std::cout << "hit the light" << std::endl;
                
                
            } else {
                //light is obstructed
                //                std::cout << "secondary ray hit an object" << std::endl;
                i->c.r *= 0.5;
                i->c.g *= 0.5;
                i->c.b *= 0.5;
            }
        }
    }
	return i;
	
}
