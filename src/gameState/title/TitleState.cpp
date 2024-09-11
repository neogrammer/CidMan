#include <gameState/title/TitleState.h>
#include <mgr/GameStateMgr.h>
#include <iostream>
TitleState::TitleState(GameStateMgr* mgr_)
	: GameState{mgr_}
{
}

void TitleState::input()
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

void TitleState::update()
{
	if (enterKeyPressed)
	{
		//popMe();
		//next = GameStateType::Title;
		mgr->changeState(GameStateType::StageSelect);
		std::cout << "Entering StageSelect" << std::endl;
	}
}

void TitleState::render(sf::RenderWindow& wnd_)
{
	sf::Sprite titleBGSpr = {};
	titleBGSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::TitleBG));
	wnd_.draw(titleBGSpr);
}
