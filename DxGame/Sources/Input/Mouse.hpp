# pragma once

# include <array>

# include "Memento.hpp"
# include "Point2.hpp"
# include "Vector3.hpp"

class Mouse
{
public:

	struct State
	{
		int input;

		Point2 position;

		int scrollValue;

		State();

		State(int input, const Point2& position, int scrollValue);
	};

public:

	Mouse();

	static void Update();

	static bool IsClicked(int keyCode);

	static bool IsPressed(int keyCode);

	static bool IsReleased(int keyCode);
	
	static Point2 Position(int numPrev = 0);

	static int ScrollValue(int numPrev = 0);

private:

	static bool IsStand(int state, int keyCode);

private:

	Memento<Mouse::State> m_states;
};
