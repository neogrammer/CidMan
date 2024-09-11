#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <res/Cfg.h>
#include <tile/Tile.h>
class Actor
{
protected:
	Cfg::Textures texType;
	sf::Vector2f pos;
	sf::Vector2i texOffset;
	sf::Vector2f size;
	sf::Vector2i texSize;
	sf::Vector2f vel;
	sf::Vector2f acc;
public:
	Actor();
	explicit Actor(Cfg::Textures texType_, sf::Vector2f pos_, sf::Vector2f size_, sf::Vector2i texOff_, sf::Vector2i texSize_);
	float findNextY(float gravity_ = 981000.f);
	float findNextX();
	void applyVel();
	sf::Vector2f getPos();
	sf::Vector2f getSize();
	void setVel(float velx_, float vely_);
	void setAcc(float xAcc, float yAcc);
	Cfg::Textures getTexType();
	void handleTileCollisions(std::vector<Tile>& tiles);
	void applyAcc(float gravity_);
	void applyAcc(float yAcc_, float gravity_);
	virtual ~Actor() = default;
	virtual void input() = 0;

	virtual void update() = 0;
	virtual void render(sf::RenderWindow& wnd_) = 0;


};