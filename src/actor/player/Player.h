#pragma once
#include <actor/Actor.h>
#include <SFML/Graphics.hpp>
class Player : public Actor
{
	const float MAXVELX = 300.f;
	bool shouldBurstLeft{ true };
	bool shouldBurstRight{ true };
	bool jumping{ false };
	sf::Clock  jumpTimer{};
	bool startJumping{ false };
	bool falling{ true };
	bool grounded{ true };

public:

	Player();
	~Player() = default;
	void input() override final;
	void update() override final;
	void render(sf::RenderWindow& wnd_) override final;
};