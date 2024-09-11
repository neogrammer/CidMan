#include <actor/player/Player.h>
#include <SFML/Window/Keyboard.hpp>
#include <misc/globals.h>
Player::Player()
  : Actor{ Cfg::Textures::PlayerAtlas, {20.f,50.f}, {60.f,78.f}, {32,45}, {130,160} }
{
}

void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (shouldBurstRight)
		{
			shouldBurstRight = false;
			shouldBurstLeft = true;
			vel.x = 200.f;
		}
		acc.x = 533.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (shouldBurstLeft)
		{
			shouldBurstLeft = false;
			shouldBurstRight = true;
			vel.x = -200.f;
		}
		acc.x = -533.f;

	}
	else
	{
		shouldBurstRight = true;
		shouldBurstLeft = true;
		acc.x = 0.f;
	}
	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (vel.y == 0.f && !falling)
		{
			startJumping = true;
			
		}
	}
}

void Player::update()
{
	if (vel.x > MAXVELX)
		vel.x = MAXVELX;
	if (vel.x < -MAXVELX)
		vel.x = -MAXVELX;

	//if (falling)
	//{
	//	//check collisions
	//	if (pos.y >= 900 - 50 - size.y)
	//	{
	//		pos.y = 900 - 50 - size.y;
	//		vel.y = 0.f;
	//		applyAcc(0.f, 0.f);
	//		falling = false;
	//	}
	//	else
	//	{
	//		// slow down acceleration
	//		acc.x *= 0.8f * gTime;
	//		//if (fabs(acc.x) < 8.f)
	//		//{
	//		//	acc.x = 0.f;
	//	//	}
	//		pos.y = findNextY();
	//		pos.x = findNextX();
	//	}
	//}
	//else
	//{
	//	pos.y = findNextY();
	//	pos.x = findNextX();
	//}

	if (jumping)
	{
		vel.y = -950.f;
		if (jumpTimer.getElapsedTime().asSeconds() > .2f)
		{
			jumping = false;
			falling = true;
			vel.y = 1900.f;
		}
	}

	if (startJumping)
	{
		startJumping = false;
		jumping = true;
		pos.y -= 1.f;
		vel.y = -750.f;

		jumpTimer.restart();
	}

	if (falling)
	{
		vel.y += 400.f;
	}
	

	////check collisions
	if (pos.y >= 900 - 50 - size.y)
	{
		pos.y = 900 - 50 - size.y;
		vel.y = 0.f;
		applyAcc(0.f,0.f);
		falling = false;
		grounded = true;
	}
	else
	{
		// slow down acceleration
		acc.x *= 0.8f * gTime;
		applyAcc(acc.y, 9810.f);
	}

	pos.x = findNextX();
	
	

	//applyVel();

}


void Player::render(sf::RenderWindow& wnd_)
{
	sf::Sprite spr(Cfg::textures.get((int)texType));
	spr.setPosition(pos - (sf::Vector2f(texOffset)));
	spr.setTextureRect({ {0 * (int)texSize.x,1 * (int)texSize.y},{texSize.x,texSize.y} });

	wnd_.draw(spr);
}
