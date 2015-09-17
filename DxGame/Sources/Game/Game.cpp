#include "Game.hpp"

# include <DxLib.h>

# include "DxLibConvert.hpp"

char buffer[256];

int handle;

int stageHandle;

MATRIX Default;

aqua::Vector3 Position = aqua::Vector3::Zero;

void Game::Initialize()
{
	// モデル読み込み
	handle = MV1LoadModel(L"kabotya.mqo");

	stageHandle = MV1LoadModel(L"ColTestStage.mqo");

	MV1SetupCollInfo(stageHandle);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	Default = GetCameraViewMatrix();

	Position = { 0.0f, 1000.0f, 0.0f };
}

void Game::Update()
{
	// キー入力の取得
	GetHitKeyStateAll(buffer);

	static const float Speed = 50.0f;

	if (buffer[KEY_INPUT_A])
	{
		Position.x -= Speed;
	}
	if (buffer[KEY_INPUT_D])
	{
		Position.x += Speed;
	}

	if (buffer[KEY_INPUT_W])
	{
		Position.z += Speed;
	}
	if (buffer[KEY_INPUT_S])
	{
		Position.z -= Speed;
	}

	const VECTOR Start =
		To(Position);
	const VECTOR End =
		To(Position + aqua::Vector3(0.0f, -10000.0f, 0.0f));

	MV1_COLL_RESULT_POLY result =
		MV1CollCheck_Line(stageHandle, -1,
		Start,
		End);

	if (result.HitFlag)
	{
		VECTOR pos =
			VAdd(result.HitPosition, VGet(0.0f, 10.0f, 0.0f));
		Position.x = pos.x;
		Position.y = pos.y;
		Position.z = pos.z;
	}
}

void LookAt(const aqua::Vector3& eye, const aqua::Vector3& at, const aqua::Vector3& up)
{
	SetCameraPositionAndTargetAndUpVec(
		To(eye), To(at), To(up));
	return;

	auto Current = GetCameraViewMatrix();

	aqua::Matrix matrix = aqua::Matrix::Identity();

	matrix = matrix.Translated(-eye);

	auto Dir = (at - eye).Normalized();

	auto Left = up.Cross(Dir);

	matrix.m[0][0] = Left.x;
	matrix.m[1][0] = Left.y;
	matrix.m[2][0] = Left.z;

	auto Up = Dir.Cross(Left);

	matrix.m[0][1] = Up.x;
	matrix.m[1][1] = Up.y;
	matrix.m[2][1] = Up.z;

	matrix.m[0][2] = Dir.x;
	matrix.m[1][2] = Dir.y;
	matrix.m[2][2] = Dir.z;

	//matrix = matrix.Inverse();

	SetCameraViewMatrix(To(matrix));
}

void Game::Render()
{
	constexpr int Width = 640;

	constexpr int Height = 480;

	SetWindowSize(Width, Height);

	// 透視射影行列
	SetupCamera_Perspective(Math::Radian * 60.0f);
	SetCameraNearFar(41.5692215f, 20415.6914f);

	// カメラ
	aqua::Matrix matrix = aqua::Matrix::Identity();
	matrix = matrix.Translated(0.0f,-100.0f, 1000.0f);
	SetCameraViewMatrix(To(matrix));

	LookAt(
	// { 0.0f, 500.0f, -1000.0f },
	Position + aqua::Vector3(0.0f, 500.0f, -1000.0f),
	Position,
	{ 0.0f, 1.0f, 0.0f });

	// kabo
	{
		aqua::Matrix model = aqua::Matrix::Identity();
		model = model.Scaled(0.3f);
		model = model.RotatedY(Math::ToRadian(0.0f));
		// model = model.Translated(200.0f, 0.0f, 0.0f);
		model = model.Translated(Position);
		MV1SetMatrix(handle, To(model));
		MV1DrawModel(handle);
	}

	// stage
	{
		aqua::Matrix model = aqua::Matrix::Identity();
		model = model.Scaled(5.0f);
		MV1SetMatrix(stageHandle, To(model));
		MV1DrawModel(stageHandle);
	}
}

void Game::Finalize()
{
	MV1DeleteModel(handle);
	MV1DeleteModel(stageHandle);

	MV1TerminateCollInfo(stageHandle);
}

bool Game::IsEnded() const
{
	return
		buffer[KEY_INPUT_ESCAPE] != 0 ||
		GetWindowUserCloseFlag();
}
