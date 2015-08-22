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

		// �`���𗠉�ʂɂ���
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
		MessageBox(NULL, aqua::String(ex.what()), L"��O���L���b�`���܂���", MB_OK);
		return false;
	}

	Finalize();

	return true;
}

void IGameFrame::Init() const
{
	if (DxLib_Init())
	{
		std::exception("DxLib�̏������Ɏ��s���܂���");
	}
}

void IGameFrame::Process() const
{
	if (ProcessMessage())
	{
		std::exception("�V�X�e�����b�Z�[�W�̏����Ɏ��s���܂���");
	}
}

void IGameFrame::Flip() const
{
	if (ScreenFlip())
	{
		std::exception("�`��X�N���[���̐؂�ւ��Ɏ��s���܂���");
	}
}

void IGameFrame::ClearScreen() const
{
	if (ClearDrawScreen())
	{
		std::exception("�`��X�N���[���̃N���A�Ɏ��s���܂���");
	}
}

void IGameFrame::ClearBackGround(int red, int green, int blue) const
{
	if (SetBackgroundColor(red, green, blue))
	{
		std::exception("�w�i�F�̏������Ɏ��s���܂���");
	}
}

void IGameFrame::WindowMode(bool isWindowed) const
{
	if (ChangeWindowMode(isWindowed))
	{
		std::exception("�E�B���h�E���[�h�̕ύX�Ɏ��s���܂���");
	}
}
