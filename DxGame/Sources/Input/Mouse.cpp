# include "Mouse.hpp"

# include "SingletonFinalizer.hpp"

# include <DxLib.h>


Mouse::State::State()
	: input(0)
	, position()
	, scrollValue(0)
{

}

Mouse::State::State(int input, const Point2& position, int scrollValue)
	: input(input)
	, position(position)
	, scrollValue(scrollValue)
{

}


Mouse::Mouse()
	: m_states(2)
{

}

void Mouse::Update()
{
	Mouse& ref = Singleton<Mouse>::Instance();
	
	Point2 p;
	GetMousePoint(&p.x, &p.y);
	ref.m_states.Emplace(GetMouseInput(), p, GetMouseWheelRotVol());
}

bool Mouse::IsClicked(int keyCode)
{
	Mouse& ref = Singleton<Mouse>::Instance();
	const int& current = ref.m_states.History(0).input;
	const int& previous = ref.m_states.History(1).input;
	return !IsStand(previous, keyCode) && IsStand(current, keyCode);
}

bool Mouse::IsPressed(int keyCode)
{
	Mouse& ref = Singleton<Mouse>::Instance();
	const int& current = ref.m_states.History(0).input;
	return IsStand(current, keyCode);
}

bool Mouse::IsReleased(int keyCode)
{
	Mouse& ref = Singleton<Mouse>::Instance();
	const int& current = ref.m_states.History(0).input;
	const int& previous = ref.m_states.History(1).input;
	return IsStand(previous, keyCode) && !IsStand(current, keyCode);
}

Point2 Mouse::Position(int numPrev)
{
	Mouse& ref = Singleton<Mouse>::Instance();
	return ref.m_states.History(numPrev).position;
}

int Mouse::ScrollValue(int numPrev)
{
	Mouse& ref = Singleton<Mouse>::Instance();
	return ref.m_states.History(numPrev).scrollValue;
}

bool Mouse::IsStand(int state, int keyCode)
{
	return (state & keyCode) != 0;
}
