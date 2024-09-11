#pragma once
#include <gameState/GameState.h>

class TitleState : public GameState
{
	bool enterKeyDown{ false };
	bool enterKeyPressReady{ false };
	bool enterKeyReleased{ true };
	bool enterKeyPressed{ false };
public:
	TitleState(GameStateMgr* mgr_);
	virtual void input();
	virtual void update();
	virtual void render(sf::RenderWindow& wnd_);
};