#include "Camera.hpp"
#include "Geometry.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include "ShapeList.hpp"

std::mutex rgb_mutex;

 void renderPart(
                int startX,
                int endX,
                int startY,
                int endY,
                Point topLeft,
                Vector perPixelV,
                Vector perPixelU,
                Point location,
                std::vector<Pixel>* rgb,
                Shape const* s){
    
    
        for (int x = startX; x < endX; ++x) {
            for (int y = startY; y < endY; ++y) {
                Point filmPoint = topLeft + perPixelV * static_cast<float>(y) + perPixelU * static_cast<float>(x);
                Ray r = * new Ray{location, filmPoint - location};
                auto hit = s->hit(r);
                
                
                if(hit) {
                    
                    //determine reflection
                    //R = 2(N dot L)N - L
                    Vector R = (hit->normal * dot(hit->normal, r.d) * 2) - r.d;
                    
                    Ray refRay = * new Ray{r.o + r.d*hit->t, R};
                    auto rf = ShapeList::getInstance().hit(refRay);
                    if(rf){
                        hit->c.r += rf->c.r;
                        hit->c.g += rf->c.g;
                        hit->c.b += rf->c.b;
                    }
                     
                    rgb_mutex.lock();
                    rgb->push_back({x,y, hit->c.r, hit->c.g, hit->c.b});
                    rgb_mutex.unlock();
                } else {
                    rgb_mutex.lock();
                    rgb->push_back({x,y, 0, 0, 0});
                    rgb_mutex.unlock();
                }
        }
    }
}


void Camera::look(Vector p){
    lookAt = p;
};

void Camera::render(Shape const& s, std::vector<Pixel>& rgb)
{
    
	auto filmCenter = location + lookAt;
	auto v = cross(lookAt, up);
	auto perPixelU = up * (height / yPixels);
	auto perPixelV = v * (width / xPixels);
	auto topLeft = filmCenter - (perPixelV * (xPixels / 2.0f)) - (perPixelU * (yPixels/2.0f));
	//For each pixel cast ray
	std::cout << "P6" << std::endl;
	std::cout << xPixels << " " << yPixels << std::endl;
	std::cout << "256" << std::endl;
	
    
    bool thread = true;
    
    if(thread){
    
        //Top Left
        std::thread q1(renderPart, 0, xPixels/2, 0, yPixels/2, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
        //Top Right
        std::thread q2(renderPart, xPixels/2, xPixels, 0, yPixels/2, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
        //Bottom Right
        std::thread q3(renderPart, 0, xPixels/2, yPixels/2, yPixels, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
        //Bottom Right
        std::thread q4(renderPart, xPixels/2, xPixels, yPixels/2, yPixels, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
        q1.join();
        q2.join();
        q3.join();
        q4.join();
    
    
    } else {
    
        //Top Left
        renderPart(0, xPixels/2, 0, yPixels/2, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
        //Top Right
        renderPart(xPixels/2, xPixels, 0, yPixels/2, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
        //Bottom Right
        renderPart(0, xPixels/2, yPixels/2, yPixels, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
        //Bottom Right
        renderPart(xPixels/2, xPixels, yPixels/2, yPixels, topLeft, perPixelV, perPixelU, location, &rgb, &s);
    
    }
     
     /*
    
    
    
    for (int i = 0; i < xPixels; ++i) {
    //parallel_for(size_t(0), size_t(xPixels), [&](size_t i){
        std::cout << "\r" << i << "/" << xPixels << std::flush;
        for (int j = 0; j < yPixels; ++j) {
            //find point on film
            Point filmPoint = topLeft + perPixelV * static_cast<float>(i) + perPixelU * static_cast<float>(j);
            //            std::cout << filmPoint << std::endl;
            Ray r = * new Ray{location, filmPoint - location};
            auto hit = s.hit(r);
            //PPM output
            if(hit) {
                rgb.push_back(Pixel{j,static_cast<int>(i), hit->c.r, hit->c.g, hit->c.b});
                
            } else {
                rgb.push_back(Pixel{j,static_cast<int>(i),0,0,0});
            }
        }
    }
     
    */
}


