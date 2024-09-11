#ifndef GAME_H__
#define GAME_H__
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <core/GameWin.h>
#include <mgr/GameStateMgr.h>
class Game
{
	sf::Clock frameTimer{};
	GameWin wnd;
	void input();
	void update();
	void render();
	GameStateMgr gameStateMgr;
public:

	Game();
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	GameWin& gWnd();
	sf::RenderWindow& rWnd();
	void run();
};

#endif