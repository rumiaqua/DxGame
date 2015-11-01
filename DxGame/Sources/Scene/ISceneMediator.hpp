# pragma once

enum class Scene;

class ISceneMediator
{
protected:

	ISceneMediator() = default;

public:

	virtual void Push(const Scene& scene) = 0;

	virtual void Push(const Scene& scene, float t, bool isSwallow = true) = 0;

	virtual void Pop() = 0;

	virtual void Pop(float t, bool isSwallow = true) = 0;

	virtual void Change(const Scene& scene) = 0;

	virtual void Change(const Scene& scene, float t, bool isSwallow = true) = 0;

	virtual void Replace(const Scene& scene) = 0;

	virtual void Replace(const Scene& scene, float t, bool isSwallow = true) = 0;
};
