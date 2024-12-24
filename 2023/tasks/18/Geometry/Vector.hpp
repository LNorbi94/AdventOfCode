#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector
{
public:
	Vector	(const double x, const double y);
	~Vector	();

	double	GetX	() const;
	double	GetY	() const;

	void	Rotate	(const double angle);

private:
	double	x;
	double	y;
};

#endif
