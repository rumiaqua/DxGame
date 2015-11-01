# include "SceneManager.hpp"

# include "IScene.hpp"
# include "Debug.hpp"
# include "FadeState.hpp"

# include "FadeIn.inl"
# include "FadeOut.inl"

SceneManager::SceneManager()
	: m_scenes()
	, m_stack()
	, m_processes()
	, m_isFade(false)
{

}

void SceneManager::Update()
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
	{
		(*it)->Update();
		if ((*it)->IsSwallow())
		{
			return;
		}
	}
}

void SceneManager::Render() const
{
	for (auto&& scene : m_stack)
	{
		scene->Render();
	}
}

void SceneManager::Resolve()
{
	for (auto&& process : m_processes)
	{
		process();
	}
	m_processes.clear();
}

void SceneManager::Push(const Scene& scene)
{
	if (HasExist(scene))
	{
		return;
	}
	AddProcess([=]
	{
		PushScene(m_scenes.at(scene));
	});
}

void SceneManager::Push(const Scene& scene, float t, bool isSwallow)
{
	if (HasExist(scene))
	{
		return;
	}
	AddProcess([=]
	{
		PushFadeOut(t, [=] { Push(scene); }, isSwallow);
	});
}

void SceneManager::Pop()
{
	AddProcess([=]
	{
		PopScene();
	});
}

void SceneManager::Pop(float t, bool isSwallow)
{
	AddProcess([=]
	{
		PushFadeOut(t, [=] { Pop(); }, isSwallow);
	});
}

void SceneManager::Change(const Scene& scene)
{
	if (HasExist(scene))
	{
		return;
	}
	AddProcess([=]
	{
		for (size_t i = 0; m_stack.size(); ++i)
		{
			PopScene();
		}
		PushScene(m_scenes.at(scene));
	});
}

void SceneManager::Change(const Scene& scene, float t, bool isSwallow)
{
	if (HasExist(scene))
	{
		return;
	}
	AddProcess([=]
	{
		PushFadeOut(t, [=] { Change(scene); }, isSwallow);
	});
}

void SceneManager::Replace(const Scene& scene)
{
	if (HasExist(scene))
	{
		return;
	}
	AddProcess([=]
	{
		PopScene();
		PushScene(m_scenes.at(scene));
	});
}

void SceneManager::Replace(const Scene& scene, float t, bool isSwallow)
{
	if (HasExist(scene))
	{
		return;
	}
	AddProcess([=]
	{
		PushFadeOut(t, [=] { Replace(scene); }, isSwallow);
	});
}

void SceneManager::PushScene(const IScenePtr& scene)
{
	m_stack.push_back(scene);
	scene->Initialize();
}

void SceneManager::PushFadeOut(float t, const std::function<void()>& process, bool isSwallow)
{
	m_isFade = true;
	PushScene(Create<FadeOut>(t, process, isSwallow, &m_isFade));
}

void SceneManager::PopScene()
{
	m_stack.back()->Finalize();
	m_stack.pop_back();
}

void SceneManager::AddProcess(const Process& process)
{
	if (m_isFade)
	{
		return;
	}
	m_processes.emplace_back(process);
}

bool SceneManager::HasExist(const IScenePtr& scene) const
{
	return std::find(m_stack.begin(), m_stack.end(), scene) != m_stack.end();
}

bool SceneManager::HasExist(const Scene& scene) const
{
	return HasExist(m_scenes.at(scene));
}
