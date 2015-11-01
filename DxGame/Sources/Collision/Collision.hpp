# pragma once

class Sphere;
class Line;

namespace Collision
{
	bool Intersects(const Sphere& sphere1, const Sphere& sphere2);

	bool Intersects(const Sphere& sphere1, const Line& line2);

	bool Intersects(const Line& line1, const Line& line2);
}
