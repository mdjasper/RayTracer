#include "ShapeList.hpp"

void ShapeList::addShape(std::unique_ptr<Shape> s)
{
	shapes.push_back(std::move(s));
}
BBox ShapeList::getBoundingBox() const
{
	BBox b;
	for (auto&& s : shapes)
	{
		b = union_(b, s->getBoundingBox());
	}
	return b;
}

std::unique_ptr<HitRecord> ShapeList::intersect(Ray r) const
{
	std::unique_ptr<HitRecord> hit = nullptr;
	for (auto&& s : shapes)
	{
		auto cur = s->hit(r);
		if (hit)
		{
			if (cur)
			{
				if (cur->t < hit->t)
				{
					std::swap(hit, cur);
				}
			}
		}
		else
		{
			std::swap(hit, cur);
		}
	}
	return hit;
}