#ifndef SHAPE_LIST_HPP
#define SHAPE_LIST_HPP

#include "Shape.hpp"
#include <vector>

class ShapeList : public Shape
{
public:
	ShapeList() :shapes(){}
	~ShapeList() = default;
	void addShape(std::unique_ptr<Shape>);
	BBox getBoundingBox() const override;
private:
	std::unique_ptr<HitRecord> intersect(Ray) const override;
	std::vector<std::unique_ptr<Shape>> shapes;
};

#endif