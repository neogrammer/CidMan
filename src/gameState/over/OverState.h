#pragma once
#include <gameState/GameState.h>

class OverState : public GameState
{
public:
	OverState(GameStateMgr* mgr_);
	virtual void input();
	virtual void update();
	virtual void render(sf::RenderWindow& wnd_);
};