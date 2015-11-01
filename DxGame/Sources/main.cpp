# include "Game/Game.hpp"

# include "Collision/Sphere.hpp"
# include "Collision/Collision.hpp"

# include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IShape* s1 = new Sphere(Vector3::Zero(), 10.0f);
	IShape* s2 = new Sphere(Vector3::Zero(), 20.0f);

	s1->Intersects(*s2);

	delete s1;
	delete s2;

	return Game().Run();
}
