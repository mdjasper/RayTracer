#include "Shape.hpp"
#include "ShapeList.hpp"
#include <iostream>
//#include <cmath>

#define MAX_RAY_DEPTH 3

Shape::~Shape(){}

bool Shape::hitP(Ray r)const {
	//test bbox intersection
	if (!::intersect(r, getBoundingBox())) return false;
	return intersectP(r);
}

std::unique_ptr<HitRecord> Shape::hit(Ray r)const {
    return hit(r, MAX_RAY_DEPTH);
}

std::unique_ptr<HitRecord> Shape::hit(Ray r, int depth)const {
	if (!::intersect(r, getBoundingBox())) return nullptr;
    auto i = intersect(r);
	if (i){
		//check lighting
		auto intersectPoint = r.o + r.d * i->t;
        
//        if(i->isGlass && depth == 0){
//            Vector refractionVector = r.d - i->normal;
//            Ray refractionRay = * new Ray{intersectPoint, refractionVector};
//            i = ShapeList::getInstance().hit(refractionRay, depth + 1);
//        } else {
        
            //For each light
            
            //create a new ray from the intersect point to the light
            Point lightLocation{1, 50, 1}; //TODO get this from scene
            
            int lightSize = 5;
            float red = 0, green = 0, blue = 0;
            for(int ix = 0; ix < lightSize; ix += 1){
            for(int iz = 0; iz < lightSize; iz += 1){
                
                Point newLightLocation = {lightLocation.x + ix*2, lightLocation.y, lightLocation.z + iz*2};
            
                Vector lightDirection = newLightLocation - intersectPoint;
                //Point LightTestPoint = intersectPoint + normalize(lightDirection) * 0.0001;
                Ray l = * new Ray{intersectPoint, lightDirection};
                
                //if the camera->shape ray also reaches the light source:
                //to create shadows
                auto lightHit = ShapeList::getInstance().hitP(l);
                float ambient = 0.3;
                
                if(!lightHit){
                    //no shapes in the way
                    //hit can see the light
                    float lightAngle = dot(normalize(lightDirection), normalize(i->normal));
          //      std::cout << lightAngle << std::endl;
                    
                    if(lightAngle < 0){
                        lightAngle = 0;
                    }
                    
                    
                
                    float reduction = lightAngle * (1-ambient) + ambient;
                    //std::cout << reduction << std::endl;
                
                    red += reduction;
                    green += reduction;
                    blue += reduction;
                } else {
                    //light is obstructed
        //            std::cout << "light ray hit an object" << std::endl;
                    red += ambient;
                    green += ambient;
                    blue += ambient;
//                    i->c.b *= ambient;
                }
            }}
            i->c.r *= red / (lightSize*lightSize);
            i->c.g *= green / (lightSize*lightSize);
            i->c.b *= blue / (lightSize*lightSize);
        }
//    }
    
	return i;
}
