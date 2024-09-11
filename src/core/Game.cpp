#include <core/Game.h>
#include <type_traits>
#include <string>
#include <misc/globals.h>
void Game::render()
{
	gameStateMgr.render(wnd.window());
}

void Game::input()
{
	gameStateMgr.input();

}

Game::Game()
	: frameTimer{}
	, wnd{ }
	, gameStateMgr{this}
{
	gTime = 0.f;
	gView = wnd.window().getDefaultView();
	gMainDefaultView = wnd.window().getDefaultView();

}

Game::~Game()
{
}



GameWin& Game::gWnd()
{
	return wnd;
}
sf::RenderWindow& Game::rWnd()
{
	return wnd.window();
}

void Game::run()
{
	
	while (rWnd().isOpen())
	{

		

		sf::Event e;
		while (rWnd().pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::KeyReleased:
				if (e.key.code == sf::Keyboard::Escape) { rWnd().close(); }
				break;
			case sf::Event::Closed:
				rWnd().close();
				break;
			default:
				break;
			}
		}

		input();

		gTime = frameTimer.restart().asSeconds();
		update();

		rWnd().clear(sf::Color(47, 147, 247, 255));
		render();
		rWnd().display();
	}	
}

void Game::update()
{
	
	gameStateMgr.update();
}