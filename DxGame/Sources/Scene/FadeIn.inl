class FadeIn final : public IScene
{
public:

	FadeIn(float fadeCount, bool isSwallow, bool* const isFade)
		: m_state(fadeCount, isSwallow)
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
		*m_isFade = true;
	}

	void Render() const override
	{
		float t = m_state.currentCount / (float)m_state.fadeCount;
		int blend = (int)(t * 255);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		DrawBox(0, 0, 100, 100, -1, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	void Finalize() override
	{
		*m_isFade = false;
	}

	bool IsSwallow() const override
	{
		return m_state.isSwallow;
	}

private:

	FadeState m_state;

	bool* const m_isFade;
};
