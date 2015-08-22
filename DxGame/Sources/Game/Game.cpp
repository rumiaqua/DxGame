#include "Game.hpp"

# include <DxLib.h>

# include "DxLibConvert.hpp"

char buffer[256];

/*// ステージの初期化処理
void Stage_Initialize(void)
{
// ステージモデルの読み込み
stg.ModelHandle = MV1LoadModel("ColTestStage.mqo");

// モデル全体のコリジョン情報のセットアップ
MV1SetupCollInfo(stg.ModelHandle, -1);
}

// ステージの後始末処理
void Stage_Terminate(void)
{
// ステージモデルの後始末
MV1DeleteModel(stg.ModelHandle);
}*/

int handle;

MATRIX Default;

void Game::Initialize()
{
	// モデル読み込み
	handle = MV1LoadModel(L"DxChara.x");

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	Default = GetCameraProjectionMatrix();
}

void Game::Update()
{
	// キー入力の取得
	GetHitKeyStateAll(buffer);
}

void Game::Render()
{
	constexpr int Width = 640;

	constexpr int Height = 480;

	SetWindowSize(Width, Height);

	// 透視射影行列
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

	// ３Ｄ空間上に球を描画する
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
