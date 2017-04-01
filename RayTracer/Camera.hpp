#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Shape.hpp"
#include "Geometry.hpp"
#include <vector>
#include <mutex>

struct Pixel{
    Pixel(int x, int y, float r, float g, float b): x(x), y(y), r(r), b(b), g(g){};
    int x, y;
    float r, g, b;
};

inline std::ostream& operator<<(std::ostream &output, Pixel p){
    output << "r: " << p.r << " g: " << p.g << " b: " << p.b << std::endl;
    return output;
}

class Camera
{
public:
    Camera(float height, float width, int xPixels, int yPixels, Point location, Vector up) : height(height), width(width), xPixels(xPixels), yPixels(yPixels), location(location), up(up){};
    void look(Vector p);
    void render(Shape const&, std::vector<Pixel>& rgb);
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
