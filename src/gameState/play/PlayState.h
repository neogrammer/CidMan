#pragma once
#include <gameState/GameState.h>
#include <memory>
#include <actor/Actor.h>

class PlayStage;

class PlayState : public GameState {
	
	std::shared_ptr<PlayStage> currStage{ };
	std::unique_ptr<Actor> player;
public:
	PlayState(GameStateMgr* mgr_);
	virtual void input();
	Actor& getPlayer();

		virtual void update();
		virtual void render(sf::RenderWindow& wnd_);
		void loadStage(StageType stage_);
};