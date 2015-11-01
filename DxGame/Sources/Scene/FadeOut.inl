class FadeOut final : public IScene
{
public:

	FadeOut(float fadeCount, const std::function<void()>& process, bool isSwallow, bool* const isFade)
		: m_state(fadeCount, isSwallow)
		, m_process(process)
		, m_isFade(isFade)
	{

	}

public:

	void Initialize() override
	{

	}

	void Update() override
	{
		m_state.currentCount = m_state.currentCount - 1.0f;

		if (m_state.currentCount > 0)
		{
			return;
		}

		*m_isFade = false;
		m_sceneMediator->Pop();
		m_process();
		SceneManager* manager =
			dynamic_cast<SceneManager*>(m_sceneMediator);
		manager->AddProcess(
			[=, count = m_state.fadeCount, isSwallow = m_state.isSwallow, isFade = m_isFade] ()
		{
			manager->PushScene(manager->Create<FadeIn>(
				count, isSwallow, isFade));
		});
		*m_isFade = true;
	}

	void Render() const override
	{
		float t = m_state.currentCount / (float)m_state.fadeCount;
		int blend = (int)(t * 255);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - blend);
		DrawBox(0, 0, 100, 100, -1, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	void Finalize() override
	{

	}

	bool IsSwallow() const override
	{
		return m_state.isSwallow;
	}

private:

	FadeState m_state;

	const std::function<void()> m_process;

	bool* const m_isFade;
};
