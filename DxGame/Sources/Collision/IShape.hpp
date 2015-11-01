# pragma once

class Sphere;
class Line;

class IShape
{
public:

	IShape() = default;

	virtual ~IShape() = default;

public:

	virtual bool Intersects(const IShape& shape) const = 0;

	virtual bool Intersects(const Sphere& shape) const = 0;

	virtual bool Intersects(const Line& shape) const = 0;
};
