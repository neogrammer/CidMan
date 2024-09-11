#pragma once
#include <gameState/GameState.h>
class GameStateMgr;
class PersistState : public GameState
{
public:
	PersistState(GameStateMgr* mgr_);
	~PersistState() = default;
	void input() override final;
	void update() override final;
	void render(sf::RenderWindow& wnd_) override final;
};