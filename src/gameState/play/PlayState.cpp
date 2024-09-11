#include <gameState/play/PlayState.h>
#include <mgr/GameStateMgr.h>
#include <playStage/intro/IntroStage.h>
#include <iostream>
#include <actor/player/Player.h>
PlayState::PlayState(GameStateMgr* mgr_)
	: GameState{mgr_}
	, player{std::make_unique<Player>()}
{
}

void PlayState::input()
{
	if (currStage)
	{
		currStage->input();
	}
	player->input();
}

Actor& PlayState::getPlayer()
{
	return *player;
}

void PlayState::update()
{
	if (currStage)
	{
		currStage->update();
	}
	player->handleTileCollisions(currStage->getTilemap().getTiles());
	player->update();
	
}

void PlayState::render(sf::RenderWindow& wnd_)
{

	if (currStage)
	{
		currStage->render(wnd_);
	}
	
	player->render(wnd_);
}

void PlayState::loadStage(StageType stage_)
{

	

	if (currStage)
	{
		currStage.reset();
	}
	switch (stage_)
	{
	case StageType::Intro:
		std::cout << "Entering Intro Stage" << std::endl;
		currStage = std::make_shared<IntroStage>(this, Cfg::Textures::TSet1, "ass/data/tset/tset1.tset", "ass/data/tmap/intro.tmap");
		break;
	default:
		break;
	}

}
