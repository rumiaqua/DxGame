# pragma once

# include "IShape.hpp"

# include "Vector3.hpp"
# include "Collision.hpp"

class Sphere : public IShape
{
public:

	Sphere(const Vector3& origin, float radius)
		: origin(origin)
		, radius(radius)
	{

	}

	virtual ~Sphere() = default;

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
		return Collision::Intersects(*this, shape);
	}

public:

	Vector3 origin;

	float radius;
};
