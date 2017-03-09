#ifndef SHAPE_LIST_HPP
#define SHAPE_LIST_HPP

#include "Shape.hpp"
#include <vector>

class ShapeList : public Shape
{
public:
    static ShapeList& getInstance(){
        static ShapeList instance;
        return instance;
    }
	void addShape(std::unique_ptr<Shape>);
	BBox getBoundingBox() const override;
private:
    ShapeList(){};
	std::unique_ptr<HitRecord> intersect(Ray) const override;
	std::vector<std::unique_ptr<Shape>> shapes;
public:
    ShapeList(ShapeList const&) = delete;
    void operator=(ShapeList const&) = delete;
};

#endif
