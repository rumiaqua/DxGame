# include "Debug.hpp"

# include "SingletonFinalizer.hpp"

Debug::Debug()
	: m_isClear(false)
	, m_fontSize(GetFontSize())
{

}

void Debug::Update()
{
	if (IsClear())
	{
		Clear();
	}
}

void Debug::SetClear(bool isClear)
{
	Singleton<Debug>::Instance().m_isClear = isClear;
}

bool Debug::IsClear()
{
	return Singleton<Debug>::Instance().m_isClear;
}

void Debug::Clear()
{
	clsDx();
}

void Debug::Show(const TCHAR* message, const TCHAR* caption, UINT style)
{
	MessageBox(NULL, message, caption, style);
}

void Debug::ChangeFontSize(int fontSize)
{
	SetFontSize(Singleton<Debug>::Instance().m_fontSize = fontSize);
}
