#include "ConvexhullCalculator.hpp"

// Geometry
#include "Geometry/Line.hpp"
#include "Geometry/CommonOperations.hpp"

#include <ranges>

ConvexhullCalculator::ConvexhullCalculator(const std::vector<Point> &points) : points(points)
{
}

ConvexhullCalculator::~ConvexhullCalculator() = default;

int64_t ConvexhullCalculator::CalculateArea()
{
	if (points.empty())
		return -1;

	// from http://www.mathwords.com/a/area_convex_polygon.htm
	area = 0.0;
	for (const auto [i, point] : std::views::enumerate(points) | std::ranges::views::reverse)
	{
		size_t j = (i + 1) % points.size();
		area -= point.GetX() * points[j].GetY();
		area += point.GetY() * points[j].GetX();
	}

	area /= 2.0;
	return static_cast<int64_t>(area);
}
