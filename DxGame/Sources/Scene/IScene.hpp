# pragma once

class ISceneMediator;
class SceneManager;

class IScene
{
public:

	friend SceneManager;

protected:

	IScene() = default;

public:

	virtual ~IScene() = default;

public:

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Render() const = 0;

	virtual void Finalize() = 0;

	virtual bool IsSwallow() const = 0;

protected:

	ISceneMediator* m_sceneMediator;
};
