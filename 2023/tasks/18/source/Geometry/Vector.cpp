// Geometry
#include "Vector.hpp"
#include "GeometryTypes.hpp"

// from stl
#include <cmath>

Vector::Vector (const double x, const  double y) :
	x	(x),
	y	(y)
{
}


Vector::~Vector () = default;


double Vector::GetX () const
{
	return x;
}


double Vector::GetY () const
{
	return y;
}

void Vector::Rotate (const double angle)
{
	double angleInRad = angle * Geometry::PI / 180.0;
	double rotatedX = x * std::cos (angleInRad) - y * std::sin (angleInRad);
	double rotatedY = x * std::sin (angleInRad) + y * std::cos (angleInRad);
	x = rotatedX;
	y = rotatedY;
}
