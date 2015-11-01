# include "Keyboard.hpp"

# include "SingletonFinalizer.hpp"

# include <DxLib.h>

Keyboard::Keyboard()
	: m_states(2)
{

}

void Keyboard::Update()
{
	Keyboard& ref = Singleton<Keyboard>::Instance();

	KeyBuffer buffer;
	GetHitKeyStateAll(buffer.data());
	ref.m_states.Save(buffer);
}

bool Keyboard::IsClicked(int keyCode)
{
	Keyboard& ref = Singleton<Keyboard>::Instance();
	return
		ref.m_states.History(1).at(keyCode) == 0 &&
		ref.m_states.History(0).at(keyCode) != 0;
}

bool Keyboard::IsPressed(int keyCode)
{
	Keyboard& ref = Singleton<Keyboard>::Instance();
	return
		ref.m_states.History(0).at(keyCode) != 0;
}

bool Keyboard::IsReleased(int keyCode)
{
	Keyboard& ref = Singleton<Keyboard>::Instance();
	return
		ref.m_states.History(1).at(keyCode) != 0 &&
		ref.m_states.History(0).at(keyCode) == 0;
}
