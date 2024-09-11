#pragma once
#include <gameState/GameState.h>

class PausedState : public GameState
{
public:
	PausedState(GameStateMgr* mgr_);
	virtual void input();
	virtual void update();
	virtual void render(sf::RenderWindow& wnd_);
};