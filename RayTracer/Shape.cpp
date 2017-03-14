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
        Point lightLocation = * new Point{0,100,10}; //TODO get this from scene
        Vector lightDirection = lightLocation - intersectPoint;
        Ray l = * new Ray{intersectPoint, lightDirection};
        
        //if the camera->shape ray also reaches the light source:
        //to create shadows
//        std::cout << ((r.o.x == lightLocation.x) && (r.o.y == lightLocation.y))<< std::endl;
        if(r.o != lightLocation){
            auto lightHit = ShapeList::getInstance().hit(l);
            if(!lightHit){
                //no shapes in the way
                //hit can see the light
//                std::cout << "light ray hit the light" << std::endl;
                float lightAngle = dot(normalize(lightDirection), normalize(i->normal));
                
                float reduction = lightAngle;
                std::cout << lightAngle << std::endl;
                
                i->c.r *= reduction;
                i->c.g *= reduction;
                i->c.b *= reduction;
                
            } else {
                //light is obstructed
//                std::cout << "light ray hit an object" << std::endl;
                i->c.r = 0;
                i->c.g = 0;
                i->c.b = 0;
            }
        } else {
//            std::cout << "2nd level ray" << std::endl;
        }
    }
	return i;
}
