#ifndef POINT_HPP
#define POINT_HPP

// Geometry
#include "Vector.hpp"

class Point
{
public:
	Point	();
	Point	(const double x, const double y);
	~Point	();

	double	GetX	() const;
	double	GetY	() const;

	double	Distance	(const Point& other) const;
	Vector	operator-	(const Point& other) const;
	bool	operator==	(const Point& other) const;
	bool	operator!=	(const Point& other) const;

private:
	double x;
	double y;
};

#endif
