# pragma once

# include "IShape.hpp"

# include "Vector3.hpp"
# include "Collision.hpp"

class Line : public IShape
{
public:

	Line(const Vector3& p0, const Vector3& p1)
		: p0(p0)
		, p1(p1)
	{

	}

	virtual ~Line() = default;

public:

	virtual bool Intersects(const IShape& shape) const override
	{
		return shape.Intersects(*this);
	}

	virtual bool Intersects(const Sphere& shape) const override
	{
		return Collision::Intersects(shape, *this);
	}

	virtual bool Intersects(const Line& shape) const override
	{
		return Collision::Intersects(shape, *this);
	}

public:

	Vector3 p0;

	Vector3 p1;
};
