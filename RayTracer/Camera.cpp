#include "Camera.hpp"
#include "Geometry.hpp"
#include <iostream>

void Camera::render(Shape const& s)
{
	auto filmCenter = location + lookAt;
	auto v = cross(lookAt, up);
	auto perPixelU = up / (height / yPixels);
	auto perPixelV = v / (width / xPixels);
	auto topLeft = filmCenter - (perPixelV * (xPixels / 2.0f)) + (perPixelU * (yPixels/2.0f));
	//For each pixel cast ray
	std::cout << "P6" << std::endl;
	std::cout << xPixels << " " << yPixels << std::endl;
	std::cout << "256" << std::endl;
	for (int i = 0; i < xPixels; ++i)
	{
		for (int j = 0; j < yPixels; ++j)
		{
			//find point on film
			auto filmPoint = topLeft + perPixelV * static_cast<float>(i) + perPixelU * static_cast<float>(j);
			Ray r{ location, filmPoint - location };
			auto hit = s.hit(r);
			//PPM output
			if (hit)
			{
				std::cout << hit->r << " " << hit->g << " " << hit->b << " ";
			}
			else
			{
				std::cout << "0 0 0 ";
			}
		}
		std::cout << std::endl;
	}
}