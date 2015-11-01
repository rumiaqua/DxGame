# pragma once

# include "ISceneMediator.hpp"
# include "IScenePtr.hpp"

# include <unordered_map>
# include <functional>

class FadeOut;

class SceneManager final : public ISceneMediator
{
public:

	friend FadeOut;

private:

	using Scenes = std::unordered_map<Scene, IScenePtr>;
	using Stack = std::list<IScenePtr>;

	using Process = std::function<void()>;
	using Processes = std::list<Process>;

public:

	/// <summary>コンストラクタ</summary>
	SceneManager();

public:

	/// <summary>シーンの生成</summary>
	template <typename Type, typename ...Args>
	IScenePtr Create(Args&& ...args)
	{
		IScenePtr scene =
			std::make_shared<Type>(std::forward<Args>(args)...);
		scene->m_sceneMediator = this;
		return scene;
	}

	/// <summary>シーンの追加</summary>
	template <typename Type, typename ...Args>
	void Add(const Scene& scene, Args&& ...args)
	{
		m_scenes.insert(std::make_pair(
			scene, Create<Type>(std::forward<Args>(args)...)));
	}

	/// <summary>更新</summary>
	void Update();

	/// <summary>描画</summary>
	void Render() const;

	/// <summary>解決</summary>
	void Resolve();

public:

	/// <summary>シーンをスタックに加える</summary>
	void Push(const Scene& scene) override;

	/// <summary>シーンをフェードしつつスタックに加える</summary>
	void Push(const Scene& scene, float t, bool isSwallow = true) override;

	/// <summary>シーンをスタックから削除する</summary>
	void Pop() override;

	/// <summary>シーンをスタックからフェードしつつ削除する</summary>
	void Pop(float t, bool isSwallow = true) override;

	/// <summary>シーンを切り替える</summary>
	void Change(const Scene& scene) override;

	/// <summary>シーンをフェードしつつ切り替える</summary>
	void Change(const Scene& scene, float t, bool isSwallow = true) override;

	/// <summary>シーンを入れ替える</summary>
	void Replace(const Scene& scene) override;

	/// <summary>シーンをフェードしつつ入れ替える</summary>
	void Replace(const Scene& scene, float t, bool isSwallow = true) override;

private:

	/// <summary>シーンをスタックに積む</summary>
	void PushScene(const IScenePtr& scene);

	/// <summary>フェードアウトシーンをスタックに積む</summary>
	void PushFadeOut(float t, const std::function<void()>& process, bool isSwallow);

	/// <summary>シーンをスタックから降ろす</summary>
	void PopScene();

	/// <summary>シーン処理を追加する</summary>
	void AddProcess(const Process& process);

	/// <summary>シーンがスタックに存在するかを返す</summary>
	bool HasExist(const IScenePtr& scene) const;

	/// <summary>シーンがスタックに存在するかを返す</summary>
	bool HasExist(const Scene& scene) const;

private:

	Scenes m_scenes;

	Stack m_stack;

	Processes m_processes;

	bool m_isFade;
};
