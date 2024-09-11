#include <actor/Actor.h>
#include <misc/globals.h>
#include <SFML/Window/Keyboard.hpp>

Actor::Actor()
	: Actor( Cfg::Textures::PlayerAtlas, { 20.f,50.f }, { 60.f,78.f }, { 32,45 }, { 130,160 })
{
}

Actor::Actor(Cfg::Textures texType_, sf::Vector2f pos_, sf::Vector2f size_, sf::Vector2i texOff_, sf::Vector2i texSize_)
	: texType{texType_}
	, pos{pos_}, size{size_}
	, texOffset{texOff_}, texSize{texSize_}
	, vel{0.f,0.f}, acc{0.f,0.f}
{

}

float Actor::findNextY(float gravity_)
{
	float ynew = pos.y + vel.y * gTime + (.5f * (gravity_ + acc.y) * (powf(gTime, 2)));
	return ynew;
}

float Actor::findNextX()
{
	auto xRange = pos.x + (vel.x * gTime);
	return xRange;
}

void Actor::applyVel()
{
	pos.x = findNextX();
	pos.y = findNextY();

}

sf::Vector2f Actor::getPos()
{
	return this->pos;
}

sf::Vector2f Actor::getSize()
{
	return this->size;
}

void Actor::setVel(float velx_, float vely_)
{
	vel.x = velx_;
	vel.y = vely_;

}

void Actor::setAcc(float xAcc, float yAcc = 0.f)
{
	acc.x = xAcc;
	acc.y = yAcc;
}

Cfg::Textures Actor::getTexType()
{
	return texType;
}

void Actor::handleTileCollisions(std::vector<Tile>& tiles)
{
	// check collisions
	sf::Vector2i cp;
	sf::Vector2i cn;
	float ct;


	bool collided{ false };

	std::vector<std::pair<int, float> > z;
	for (int i = 0; i < tiles.size(); i++)
	{
		collided = true;
		sf::Vector2f targetPos;
		sf::Vector2f targetSize;
		targetPos = { tiles[i].getPos().x, tiles[i].getPos().y };
		targetSize = { 50.f,50.f };
		Cfg::Textures tmpTex = Cfg::Textures::TSet1;
		if (tiles[i].getSolid() == true)
		{
			if (phys::DynamicRectVsRect(this->pos, this->size, this->vel, targetPos, targetSize, cp, cn, ct, gTime))
			{
				if (cn.y == -1)
				{
					this->setAcc(0.f);
				}
				z.push_back({ i, ct });

			}
		}
	}

	// sort
	std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
		{
			return a.second < b.second;
		});


	// resolve in correct order
	for (auto j : z)
	{
		sf::Vector2f targetPos;
		sf::Vector2f targetSize;
		targetPos = { tiles[j.first].getPos().x, tiles[j.first].getPos().y};
		targetSize = { 50.f,50.f };
		Cfg::Textures tmpTex = Cfg::Textures::TSet1;

		if (phys::DynamicRectVsRect(this->pos, this->size, this->vel, targetPos, targetSize, cp, cn, j.second, gTime))
		{
			if (cn.y == -1)
				this->vel += { cn.x * sf::Vector2f{ std::abs(this->vel.x), std::abs(this->vel.y) }.x * (1 - j.second), cn.y * sf::Vector2f{ std::abs(this->vel.x), std::abs(this->vel.y) }.y * (1 - j.second) };
		}
	}

	if (collided)
	{
		this->pos += this->vel * gTime;
		this->vel.y = 0.f;
	}

}

void Actor::applyAcc(float gravity_)
{
	vel.x = vel.x + (acc.x * gTime);
	if (acc.y == 0.f && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))// && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		vel.x *= 0.989f;
		if (fabs(vel.x) <= 5.f and (vel.y == 0.f))
		{
			vel.x = 0;
		}
	}
	
	vel.y = vel.y + ((acc.y+gravity_) * gTime);
}


void Actor::applyAcc(float yAcc_, float gravity_)
{
	vel.x = vel.x + (acc.x * gTime);
	if (acc.y == 0.f && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)  && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		vel.x *= 0.989f;
		if (fabs(vel.x) <= 5.f and (vel.y == 0.f))
		{
			vel.x = 0;
		}
	}
	vel.y = vel.y + (yAcc_ + gravity_) * gTime;
}

