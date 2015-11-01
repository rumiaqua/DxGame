# pragma once

# include "Scene/SceneManager.hpp"

class Game
{
public:

	virtual ~Game();

public:

	bool Run();

private:

	void Initialize();

	void Update();
	
	void Render();
	
	void Finalize();
	
	bool IsEnd() const;

	void Init() const;

	void Process() const;

	void Flip() const;

	void ClearScreen() const;

	void ClearBackGround(int red, int green, int blue) const;

	void SetWindowMode(bool isWindowed) const;

private:

	SceneManager m_sceneManager;
};
