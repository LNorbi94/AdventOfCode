#ifndef LINE_HPP
#define LINE_HPP

// from stl
#include <vector>

// Geometry
#include "Point.hpp"

class Line
{
public:
	Line(const Point &start, const Point &end);
	~Line();

	const Point &GetStart() const;
	const Point &GetEnd() const;

private:
	Point start;
	Point end;
};

#endif
