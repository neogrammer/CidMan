#pragma once
#include <SFML/Graphics.hpp>
class Tile
{
	bool solid{ false };
	sf::IntRect texRect{};
	sf::Vector2f pos{};
public:
	Tile() = default;
	Tile(bool c_, sf::IntRect iRect_, sf::Vector2f pos_);
	~Tile() = default;
	bool getSolid();
	void setSolid(bool c_);
	sf::IntRect getTexRect();
	void setTexRect(sf::IntRect iRect_);
	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos_);
	void setup(bool c_, sf::IntRect iRect_, sf::Vector2f pos_);
	Tile(const Tile&) = default;
	Tile& operator=(const Tile&) = default;
	Tile(Tile&&) = default;
	Tile& operator=(Tile&&) = default;
};