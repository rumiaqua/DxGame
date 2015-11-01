#include "Game.hpp"

# include "Math.hpp"
# include "Matrix.hpp"
# include "Vector3.hpp"
# include "String.hpp"
# include "SingletonFinalizer.hpp"

# include "Input/Keyboard.hpp"
# include "Input/Mouse.hpp"

# include "Scene/TestScene.hpp"
# include "Scene/TestScene2.hpp"

# include <DxLib.h>

Game::~Game()
{
	DxLib_End();
}

void Game::Initialize()
{
	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	Debug::SetClear(true);

	m_sceneManager.Add<TestScene>(Scene::TestScene);
	m_sceneManager.Add<TestScene2>(Scene::TestScene2);

	m_sceneManager.Push(Scene::TestScene);
}

void Game::Update()
{
	//入力情報力の更新
	Keyboard::Update();
	Mouse::Update();
	Debug::Update();

	m_sceneManager.Resolve();
	m_sceneManager.Update();
}

void Game::Render()
{
	m_sceneManager.Render();
}

void Game::Finalize()
{
	SingletonFinalizer::Finalize();
}

bool Game::IsEnd() const
{
	return
		Keyboard::IsClicked(KEY_INPUT_ESCAPE) ||
		GetWindowUserCloseFlag();
}

bool Game::Run()
{
	try
	{
		ClearBackGround(32, 32, 32);

		SetWindowMode(true);

		// 描画先を裏画面にする
		SetDrawScreen(DX_SCREEN_BACK);

		Init();

		Initialize();

		while (!IsEnd())
		{
			Process();

			Update();

			ClearScreen();

			Render();

			Flip();
		}
	}
	catch (const std::exception& ex)
	{
		MessageBox(NULL, String(ex.what()).ToWide().c_str(), L"例外をキャッチしました", MB_OK);
		return false;
	}

	Finalize();

	return true;
}

void Game::Init() const
{
	if (DxLib_Init())
	{
		std::exception("DxLibの初期化に失敗しました");
	}
}

void Game::Process() const
{
	if (ProcessMessage())
	{
		std::exception("システムメッセージの処理に失敗しました");
	}
}

void Game::Flip() const
{
	if (ScreenFlip())
	{
		std::exception("描画スクリーンの切り替えに失敗しました");
	}
}

void Game::ClearScreen() const
{
	if (ClearDrawScreen())
	{
		std::exception("描画スクリーンのクリアに失敗しました");
	}
}

void Game::ClearBackGround(int red, int green, int blue) const
{
	if (SetBackgroundColor(red, green, blue))
	{
		std::exception("背景色の初期化に失敗しました");
	}
}

void Game::SetWindowMode(bool isWindowed) const
{
	if (ChangeWindowMode(isWindowed))
	{
		std::exception("ウィンドウモードの変更に失敗しました");
	}
}
