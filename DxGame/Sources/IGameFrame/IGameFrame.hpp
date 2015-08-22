# pragma once

class IGameFrame
{
public:

	virtual ~IGameFrame();

public:

	bool Run();

private:

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Render() = 0;

	virtual void Finalize() = 0;

	virtual bool IsEnded() const = 0;

protected:

	void Init() const;

	void Process() const;

	void Flip() const;

	void ClearScreen() const;

	void ClearBackGround(int red, int green, int blue) const;

	void WindowMode(bool isWindowed) const;
};
