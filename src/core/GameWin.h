#pragma once
#include <SFML/Graphics.hpp>
class GameWin
{
	sf::RenderWindow wnd;
public:
	GameWin();
	~GameWin() = default;
	GameWin(GameWin&&) = default;
	GameWin& operator=(GameWin&&) = default;
	GameWin(const GameWin&) = delete;
	GameWin& operator=(const GameWin&) = delete;

	sf::RenderWindow& window();

};