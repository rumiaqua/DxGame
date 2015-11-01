# pragma once

# include "Memento.hpp"

# include <array>

class Keyboard
{
private:

	using KeyBuffer = std::array<char, 256>;

public:

	Keyboard();

	static void Update();

	static bool IsClicked(int keyCode);

	static bool IsPressed(int keyCode);

	static bool IsReleased(int keyCode);

private:

	Memento<KeyBuffer> m_states;
};
