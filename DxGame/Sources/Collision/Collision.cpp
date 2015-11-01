# include "Collision.hpp"

# include "Sphere.hpp"
# include "Line.hpp"

namespace Collision
{
	bool Intersects(const Sphere& sphere1, const Sphere& sphere2)
	{
		float d = sphere1.radius + sphere2.radius;

		return Vector3::Dot(sphere1.origin, sphere2.origin) <= d * d;
	}

	bool Intersects(const Sphere& sphere1, const Line& line2)
	{
		Vector3 v1 = line2.p1 - line2.p0;
		Vector3 v2 = sphere1.origin - line2.p0;
		float t = Vector3::Dot(v2, v1) / Vector3::Dot(v1, v1);

		Vector3 vt;

		if (t < 0.0f)
		{
			vt = line2.p0;
		}
		else if (t < 1.0f)
		{
			vt = line2.p0 + v1 * t;
		}
		else if (1.0f < t)
		{
			vt = line2.p1;
		}

		Vector3 direction = sphere1.origin - vt;
		float distance = Vector3::Length(direction);
		return sphere1.radius >= distance;
	}

	bool Intersects(const Line& line1, const Line& line2)
	{
		Vector3 a = line1.p1 - line1.p0;
		Vector3 b = line2.p1 - line2.p0;
		Vector3 c = line2.p0 - line1.p0;

		Vector3 n1 = Vector3::Cross(a, b);

		if (Vector3::LengthSquared(n1) == 0.0f)
		{
			return false;
		}

		Vector3 n2 = Vector3::Cross(a, c);

		if (Vector3::LengthSquared(n2) == 0.0f)
		{
			return true;
		}

		return Vector3::Dot(n1, n2) == 0.0f;
	}
}
