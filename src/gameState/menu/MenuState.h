#pragma once
#include <gameState/GameState.h>

class MenuState : public GameState
{
public:
	MenuState(GameStateMgr* mgr_);
	virtual void input();
		virtual void update();
		virtual void render(sf::RenderWindow& wnd_);
};