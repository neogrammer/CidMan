#include <gameState/stageSelect/StageSelectState.h>
#include <mgr/GameStateMgr.h>
#include <iostream>
StageSelectState::StageSelectState(GameStateMgr* mgr_)
	: GameState{mgr_}
{
}

void StageSelectState::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		enterKeyDown = true;
		enterKeyReleased = false;
		enterKeyPressReady = true;
	}
	else
	{
		if (enterKeyDown)
		{
			enterKeyReleased = true;
			enterKeyDown = false;
		}
		else
		{
			enterKeyDown = false;
		}
	}

	if (enterKeyPressReady && enterKeyReleased)
	{
		enterKeyPressReady = false;
		enterKeyPressed = true;
	}
	else
	{
		enterKeyPressed = false;
	}

}

void StageSelectState::update()
{
	if (enterKeyPressed)
	{
		//popMe();
		//next = GameStateType::Title;
		mgr->changeState(GameStateType::Play, true, StageType::Intro);
		std::cout << "Entering the PlayState" << std::endl;
	}
}

void StageSelectState::render(sf::RenderWindow& wnd_)
{
	sf::Sprite bgImg;
	bgImg.setTexture(Cfg::textures.get((int)Cfg::Textures::StageSelectBG));
	wnd_.draw(bgImg);
}
