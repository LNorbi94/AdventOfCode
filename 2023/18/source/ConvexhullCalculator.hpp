#pragma once

// from stl
#include <vector>
#include <ostream>

// Geometry
#include "Geometry/Point.hpp"

class ConvexhullCalculator
{
public:
	ConvexhullCalculator(const std::vector<Point> &points);
	~ConvexhullCalculator();

	int64_t CalculateArea();

private:

	std::vector<Point> points;

	std::vector<Point> convexhull;
	double area;
};
