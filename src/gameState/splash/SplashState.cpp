#include <gameState/splash/SplashState.h>
#include <SFML/Graphics/Sprite.hpp>
#include <res/Cfg.h>
#include <iostream>
#include <mgr/GameStateMgr.h>
SplashState::SplashState(GameStateMgr* mgr_)
	: GameState{mgr_}
{
}
void SplashState::input()
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

void SplashState::update()
{
	if (enterKeyPressed)
	{
		//popMe();
		//next = GameStateType::Title;
		mgr->changeState(GameStateType::Title);
		std::cout << "Enter Key Pressed and Released, full motion, one time" << std::endl;
	}
}

void SplashState::render(sf::RenderWindow& wnd_)
{
	sf::Sprite logoSpr = {};
	logoSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::LogoBG));
	wnd_.draw(logoSpr);
}
