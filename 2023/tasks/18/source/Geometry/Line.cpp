// Geometry
#include "Line.hpp"

Line::Line(const Point &start, const Point &end) : start(start),
												   end(end)
{
}

Line::~Line() = default;

const Point &Line::GetStart() const
{
	return start;
}

const Point &Line::GetEnd() const
{
	return end;
}
