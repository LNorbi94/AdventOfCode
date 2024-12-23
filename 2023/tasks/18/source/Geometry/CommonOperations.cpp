// Geometry
#include "CommonOperations.hpp"
#include "GeometryTypes.hpp"

namespace Geometry
{
	bool IsPointLeftOfLine(const Point &point, const Line &line)
	{
		double d = (point.GetX() - line.GetStart().GetX()) * (line.GetEnd().GetY() - line.GetStart().GetY()) - (point.GetY() - line.GetStart().GetY()) * (line.GetEnd().GetX() - line.GetStart().GetX());
		return d < 0;
	}

	bool IsEqual(const double a, const double b)
	{
		const double diff = a - b;
		return diff < Geometry::EPS && -diff < Geometry::EPS;
	}
}
