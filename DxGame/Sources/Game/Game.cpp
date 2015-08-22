#include "Game.hpp"

# include <DxLib.h>

# include "DxLibConvert.hpp"

char buffer[256];

/*// �X�e�[�W�̏���������
void Stage_Initialize(void)
{
// �X�e�[�W���f���̓ǂݍ���
stg.ModelHandle = MV1LoadModel("ColTestStage.mqo");

// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
MV1SetupCollInfo(stg.ModelHandle, -1);
}

// �X�e�[�W�̌�n������
void Stage_Terminate(void)
{
// �X�e�[�W���f���̌�n��
MV1DeleteModel(stg.ModelHandle);
}*/

int handle;

MATRIX Default;

void Game::Initialize()
{
	// ���f���ǂݍ���
	handle = MV1LoadModel(L"DxChara.x");

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	Default = GetCameraProjectionMatrix();
}

void Game::Update()
{
	// �L�[���͂̎擾
	GetHitKeyStateAll(buffer);
}

void Game::Render()
{
	constexpr int Width = 640;

	constexpr int Height = 480;

	SetWindowSize(Width, Height);

	// �����ˉe�s��
	SetupCamera_ProjectionMatrix(Default);

	SetupCamera_Perspective(Math::ToRadian(60.0f));
	auto perspective = GetCameraProjectionMatrix();

	aqua::Matrix m = DirectX::XMMatrixPerspectiveFovLH(
		Math::ToRadian(45.0f), (float)Width / Height, 0.1f, 1000.0f);
	SetupCamera_ProjectionMatrix(To(m));
	auto proj = GetCameraProjectionMatrix();

	/*
	aqua::Matrix matrix = aqua::Matrix::Identity();
	matrix = matrix.Translated(0.0f, 0.0f, 10.0f);
	SetCameraViewMatrix(To(matrix));*/

	auto view = GetCameraViewMatrix();
	auto projection = GetCameraProjectionMatrix();

	MV1SetPosition(handle, VGet(400.0f, -100.0f, 0.0f));
	MV1DrawModel(handle);

	// �R�c��ԏ�ɋ���`�悷��
	// DrawSphere3D({ 0, 0, 0 }, 1.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void Game::Finalize()
{
	MV1DeleteModel(handle);
}

bool Game::IsEnded() const
{
	return
		buffer[KEY_INPUT_ESCAPE] != 0 ||
		GetWindowUserCloseFlag();
}
