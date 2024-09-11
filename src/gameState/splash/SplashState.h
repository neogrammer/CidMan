#pragma once
#include <gameState/GameState.h>

class SplashState : public GameState
{
	bool enterKeyDown{ false };
	bool enterKeyPressReady{ false };
	bool enterKeyReleased{ true };
	bool enterKeyPressed{ false };



public:
	SplashState(GameStateMgr* mgr_);
	virtual void input();	
	virtual void update();
	virtual void render(sf::RenderWindow& wnd_);
};