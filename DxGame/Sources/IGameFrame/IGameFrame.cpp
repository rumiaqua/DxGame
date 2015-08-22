# include "IGameFrame.hpp"

# include <DxLib.h>

# include <exception>

# include "String/String.hpp"

IGameFrame::~IGameFrame()
{
	DxLib_End();
}

bool IGameFrame::Run()
{
	try
	{
		ClearBackGround(32, 32, 32);

		WindowMode(true);

		// 描画先を裏画面にする
		SetDrawScreen(DX_SCREEN_BACK);

		Init();

		Initialize();

		while (!IsEnded())
		{
			Process();

			ClearScreen();

			Update();

			Render();

			Flip();
		}
	}
	catch (const std::exception& ex)
	{
		MessageBox(NULL, aqua::String(ex.what()), L"例外をキャッチしました", MB_OK);
		return false;
	}

	Finalize();

	return true;
}

void IGameFrame::Init() const
{
	if (DxLib_Init())
	{
		std::exception("DxLibの初期化に失敗しました");
	}
}

void IGameFrame::Process() const
{
	if (ProcessMessage())
	{
		std::exception("システムメッセージの処理に失敗しました");
	}
}

void IGameFrame::Flip() const
{
	if (ScreenFlip())
	{
		std::exception("描画スクリーンの切り替えに失敗しました");
	}
}

void IGameFrame::ClearScreen() const
{
	if (ClearDrawScreen())
	{
		std::exception("描画スクリーンのクリアに失敗しました");
	}
}

void IGameFrame::ClearBackGround(int red, int green, int blue) const
{
	if (SetBackgroundColor(red, green, blue))
	{
		std::exception("背景色の初期化に失敗しました");
	}
}

void IGameFrame::WindowMode(bool isWindowed) const
{
	if (ChangeWindowMode(isWindowed))
	{
		std::exception("ウィンドウモードの変更に失敗しました");
	}
}
