# pragma once

# include "IScene.hpp"

# include "Debug.hpp"
# include "Input/Keyboard.hpp"
# include "ISceneMediator.hpp"
# include "Scene.hpp"

class TestScene2 : public IScene
{
private:

	Vector3 m_position;

public:

	TestScene2() = default;

	virtual ~TestScene2() = default;

public:

	virtual void Initialize() override
	{
		m_position = Vector3::Zero();
	}

	virtual void Update() override
	{
		if (Keyboard::IsClicked(KEY_INPUT_1))
		{
			m_sceneMediator->Pop(30.0f);
		}
		if (Keyboard::IsClicked(KEY_INPUT_2))
		{
			m_sceneMediator->Pop();
		}

		constexpr float Speed = 20.0f;
		if (Keyboard::IsPressed(KEY_INPUT_A))
		{
			m_position += Vector3::Left() * Speed;
		}
		if (Keyboard::IsPressed(KEY_INPUT_D))
		{
			m_position += Vector3::Right() * Speed;
		}
	}

	virtual void Render() const override
	{
		Debug::Println("ぴよぱんだ");

		constexpr int Width = 640;

		constexpr int Height = 480;

		SetWindowSize(Width, Height);

		// 透視射影行列
		Matrix projection = Matrix::Perspective(
			Math::ToRadian(45.0), 1.33334f, 1.0f, 10000.0f);
		SetupCamera_ProjectionMatrix(projection);

		// ビュー行列
		Matrix view = Matrix::LookAt(
			Vector3(0.0f, 0.0f, -500.0f) + m_position, Vector3::Zero(), Vector3::Up());
		SetCameraViewMatrix(view);

		// スフィア
		struct Sphere
		{
			VECTOR pos;
			float r;
		};

		Sphere s1 { { 0.0f, 0.0f, 0.0f }, 80.0f };
		Sphere s2 { { 140.0f, 0.0f, 0.0f }, 40.0f };

		bool hitCheck =
			HitCheck_Sphere_Sphere(s1.pos, s1.r, s2.pos, s2.r) != 0;

		DrawSphere3D(s1.pos, s1.r, 8,
			GetColor(255, 0, 0), GetColor(255, 255, 255), hitCheck);
		DrawSphere3D(s2.pos, s2.r, 8,
			GetColor(0, 255, 0), GetColor(255, 255, 255), hitCheck);

	}

	virtual void Finalize() override
	{

	}

	virtual bool IsSwallow() const override
	{
		return false;
	}
};
