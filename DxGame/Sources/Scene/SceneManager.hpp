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

	/// <summary>�R���X�g���N�^</summary>
	SceneManager();

public:

	/// <summary>�V�[���̐���</summary>
	template <typename Type, typename ...Args>
	IScenePtr Create(Args&& ...args)
	{
		IScenePtr scene =
			std::make_shared<Type>(std::forward<Args>(args)...);
		scene->m_sceneMediator = this;
		return scene;
	}

	/// <summary>�V�[���̒ǉ�</summary>
	template <typename Type, typename ...Args>
	void Add(const Scene& scene, Args&& ...args)
	{
		m_scenes.insert(std::make_pair(
			scene, Create<Type>(std::forward<Args>(args)...)));
	}

	/// <summary>�X�V</summary>
	void Update();

	/// <summary>�`��</summary>
	void Render() const;

	/// <summary>����</summary>
	void Resolve();

public:

	/// <summary>�V�[�����X�^�b�N�ɉ�����</summary>
	void Push(const Scene& scene) override;

	/// <summary>�V�[�����t�F�[�h���X�^�b�N�ɉ�����</summary>
	void Push(const Scene& scene, float t, bool isSwallow = true) override;

	/// <summary>�V�[�����X�^�b�N����폜����</summary>
	void Pop() override;

	/// <summary>�V�[�����X�^�b�N����t�F�[�h���폜����</summary>
	void Pop(float t, bool isSwallow = true) override;

	/// <summary>�V�[����؂�ւ���</summary>
	void Change(const Scene& scene) override;

	/// <summary>�V�[�����t�F�[�h���؂�ւ���</summary>
	void Change(const Scene& scene, float t, bool isSwallow = true) override;

	/// <summary>�V�[�������ւ���</summary>
	void Replace(const Scene& scene) override;

	/// <summary>�V�[�����t�F�[�h������ւ���</summary>
	void Replace(const Scene& scene, float t, bool isSwallow = true) override;

private:

	/// <summary>�V�[�����X�^�b�N�ɐς�</summary>
	void PushScene(const IScenePtr& scene);

	/// <summary>�t�F�[�h�A�E�g�V�[�����X�^�b�N�ɐς�</summary>
	void PushFadeOut(float t, const std::function<void()>& process, bool isSwallow);

	/// <summary>�V�[�����X�^�b�N����~�낷</summary>
	void PopScene();

	/// <summary>�V�[��������ǉ�����</summary>
	void AddProcess(const Process& process);

	/// <summary>�V�[�����X�^�b�N�ɑ��݂��邩��Ԃ�</summary>
	bool HasExist(const IScenePtr& scene) const;

	/// <summary>�V�[�����X�^�b�N�ɑ��݂��邩��Ԃ�</summary>
	bool HasExist(const Scene& scene) const;

private:

	Scenes m_scenes;

	Stack m_stack;

	Processes m_processes;

	bool m_isFade;
};
