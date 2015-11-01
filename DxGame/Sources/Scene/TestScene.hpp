# pragma once

# include "IScene.hpp"

# include "Debug.hpp"
# include "Input/Keyboard.hpp"
# include "ISceneMediator.hpp"
# include "Scene.hpp"

class TestScene : public IScene
{
public:

	TestScene() = default;

	virtual ~TestScene() = default;

public:

	virtual void Initialize() override
	{

	}

	virtual void Update() override
	{
		if (Keyboard::IsClicked(KEY_INPUT_RETURN))
		{
			m_sceneMediator->Push(Scene::TestScene2, 30.0f, true);
		}
	}

	virtual void Render() const override
	{
		Debug::Println("‚Ù‚°‚Ï‚ñ‚¾");
	}

	virtual void Finalize() override
	{

	}

	virtual bool IsSwallow() const override
	{
		return true;
	}
};
