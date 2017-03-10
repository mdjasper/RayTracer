#include "Shape.hpp"
#include "ShapeList.hpp"
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
		//create a new ray from the intersect point to the light
        Ray l{intersectPoint, lightDirection};
        //if the camera->shape ray also reaches the light source:
        //to create shadows
//        if(! ShapeList::getInstance().hit(l)){
    
    
        
            float red, green, blue; //TODO get matieral color info
            red = 255;
            green = 0;
            blue = 0;
    
            float baseColorValue = dot(normalize(r.d), normalize(l.d) + i->normal);
        
            if(baseColorValue > 1){
                std::cout << baseColorValue << "\n";
            }
        
//          std::cout << baseColorValue << "\n";
        
//          baseColorValue = dot(l, i->n);
        
            i->r = red * baseColorValue;
            i->g = green * baseColorValue;
            i->b = blue * baseColorValue;
        
//        } else {
//            std::cout << "secondary ray hit an object" << std::endl;
//        }
    }
	return i;
	
}
