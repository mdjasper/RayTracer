#include "Shape.hpp"
#include "ShapeList.hpp"
#include <iostream>
//#include <cmath>



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
        Point lightLocation{0, 100, 0}; //TODO get this from scene
        Vector lightDirection = lightLocation - intersectPoint;
        //Point LightTestPoint = intersectPoint + normalize(lightDirection) * 0.0001;
        Ray l = * new Ray{intersectPoint, lightDirection};
        
        //if the camera->shape ray also reaches the light source:
        //to create shadows
        auto lightHit = ShapeList::getInstance().hitP(l);
        float ambient = 0.5;
        
        if(!lightHit){
            //no shapes in the way
            //hit can see the light
            float lightAngle = dot(normalize(lightDirection), normalize(i->normal));
  //      std::cout << lightAngle << std::endl;
            
            if(lightAngle < 0){
                lightAngle = 0;
            }
            
            
        
            float reduction =lightAngle * (1-ambient) + ambient;
            //std::cout << reduction << std::endl;
        
            i->c.r *= reduction;
            i->c.g *= reduction;
            i->c.b *= reduction;
        } else {
            //light is obstructed
//            std::cout << "light ray hit an object" << std::endl;
            i->c.r *= ambient;
            i->c.g *= ambient;
            i->c.b *= ambient;
        }
    }
	return i;
}
