#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Shape.hpp"
#include "Geometry.hpp"
#include <vector>

class Camera
{
public:
    Camera(float height, float width, int xPixels, int yPixels, Point location, Vector up) : height(height), width(width), xPixels(xPixels), yPixels(yPixels), location(location), up(up){};
    void look(Vector p);
    void render(Shape const&, std::vector<float>& rgb);
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
