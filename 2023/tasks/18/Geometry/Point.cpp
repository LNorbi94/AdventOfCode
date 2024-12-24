// Geometry
#include "Point.hpp"
#include "CommonOperations.hpp"

// from stl
#include <cmath>

Point::Point () = default;


Point::Point (const double x, const double y) :
	x	(x),
	y	(y)
{
}


Point::~Point () = default;


double Point::GetX () const
{
	return x;
}

double Point::GetY () const
{
	return y;
}


double Point::Distance (const Point& other) const
{
	double xDiff = x - other.x;
	double yDiff = y - other.y;
	return std::sqrt (std::pow (xDiff, 2.0) + std::pow (yDiff, 2.0));
}


Vector	Point::operator- (const Point& other) const
{
	return Vector (x - other.x, y - other.y);
}

bool Point::operator==(const Point& other) const
{
	return Geometry::IsEqual (x, other.x) && Geometry::IsEqual (y, other.y);
}

bool Point::operator!=(const Point & other) const
{
	return !(*this == other);
}
