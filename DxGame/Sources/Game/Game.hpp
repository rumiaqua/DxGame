# pragma once

# include "IGameFrame/IGameFrame.hpp"

class Game : public IGameFrame
{
private:

	virtual void Initialize() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void Finalize() override;

	virtual bool IsEnded() const override;
};
