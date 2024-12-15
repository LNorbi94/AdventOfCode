#pragma once

// Geometry
#include "Point.hpp"
#include "Line.hpp"

namespace Geometry
{
	bool IsPointLeftOfLine(const Point &point, const Line &line);
	bool IsEqual(const double a, const double b);
}
