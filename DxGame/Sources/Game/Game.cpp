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
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	Debug::SetClear(true);

	m_sceneManager.Add<TestScene>(Scene::TestScene);
	m_sceneManager.Add<TestScene2>(Scene::TestScene2);

	m_sceneManager.Push(Scene::TestScene);
}

void Game::Update()
{
	//���͏��͂̍X�V
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

		// �`���𗠉�ʂɂ���
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
		MessageBox(NULL, String(ex.what()).ToWide().c_str(), L"��O���L���b�`���܂���", MB_OK);
		return false;
	}

	Finalize();

	return true;
}

void Game::Init() const
{
	if (DxLib_Init())
	{
		std::exception("DxLib�̏������Ɏ��s���܂���");
	}
}

void Game::Process() const
{
	if (ProcessMessage())
	{
		std::exception("�V�X�e�����b�Z�[�W�̏����Ɏ��s���܂���");
	}
}

void Game::Flip() const
{
	if (ScreenFlip())
	{
		std::exception("�`��X�N���[���̐؂�ւ��Ɏ��s���܂���");
	}
}

void Game::ClearScreen() const
{
	if (ClearDrawScreen())
	{
		std::exception("�`��X�N���[���̃N���A�Ɏ��s���܂���");
	}
}

void Game::ClearBackGround(int red, int green, int blue) const
{
	if (SetBackgroundColor(red, green, blue))
	{
		std::exception("�w�i�F�̏������Ɏ��s���܂���");
	}
}

void Game::SetWindowMode(bool isWindowed) const
{
	if (ChangeWindowMode(isWindowed))
	{
		std::exception("�E�B���h�E���[�h�̕ύX�Ɏ��s���܂���");
	}
}
