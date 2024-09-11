#pragma once
#include <SFML/Graphics/View.hpp>

extern float gTime;
extern sf::View gView;
extern sf::View gMainDefaultView;

namespace phys
{

	extern bool PointVsRect(const sf::Vector2f& p, const sf::Vector2f& rPos, const sf::Vector2f& rSize);


	extern bool RectVsRect(const sf::Vector2f& r1Pos, const sf::Vector2f& r1Size, const sf::Vector2f& r2Pos, const sf::Vector2f& r2Size);


	extern bool RayVsRect(const sf::Vector2f ray_origin, const sf::Vector2f& ray_dir, const sf::Vector2f& targetPos, const sf::Vector2f& targetSize, sf::Vector2i& contact_point, sf::Vector2i& contact_normal, float& t_hit_near);


	extern bool DynamicRectVsRect(const sf::Vector2f& r1Pos, const sf::Vector2f& r1Size, sf::Vector2f velIn,  const sf::Vector2f & rTargetPos, const sf::Vector2f& rTargetSize, sf::Vector2i& contact_point, sf::Vector2i& contact_normal, float& contact_time, float fElapsedTime);
}

