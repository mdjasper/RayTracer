#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Shape.hpp"
#include "Geometry.hpp"

class Camera
{
public:
	Camera(){}
	void render(Shape const&);
private:
	Point location;
	Vector lookAt;
	Vector up;
	//TODO deal with non pinhole cameras
	//float aperature()
	float height, width;
	int xPixels, yPixels;
};

#endif