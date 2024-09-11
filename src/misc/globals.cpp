#include <misc/globals.h>2
#include <cmath>
float gTime = {};
sf::View gView = {};
sf::View gMainDefaultView;



bool phys::PointVsRect(const sf::Vector2f& p, const sf::Vector2f& rPos, const sf::Vector2f& rSize)
{
	return (p.x >= rPos.x && p.y >= rPos.y && p.x < rPos.x + rSize.x && p.y < rPos.y + rSize.y);
}

bool phys::RectVsRect(const sf::Vector2f& r1Pos, const sf::Vector2f& r1Size, const sf::Vector2f& r2Pos, const sf::Vector2f& r2Size)
{
	return (r1Pos.x < r2Pos.x + r2Size.x && r1Pos.x + r1Size.x > r2Pos.x && r1Pos.y < r2Pos.y + r2Size.y && r1Pos.y + r1Size.y > r2Pos.y);
}

bool phys::RayVsRect(const sf::Vector2f ray_origin, const sf::Vector2f& ray_dir, const sf::Vector2f& targetPos, const sf::Vector2f& targetSize, sf::Vector2i& contact_point, sf::Vector2i& contact_normal, float& t_hit_near)
{
	sf::Vector2f t_near = { (targetPos.x - ray_origin.x) / ray_dir.x , (targetPos.y - ray_origin.y) / ray_dir.y };
	sf::Vector2f t_far = { (targetPos.x + targetSize.x - ray_origin.x) / ray_dir.x ,  (targetPos.y + targetSize.y - ray_origin.y) / ray_dir.y };
	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;
	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;
	t_hit_near = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);
	if (t_hit_far < 0) return false;
	contact_point = (sf::Vector2i(ray_origin + t_hit_near * ray_dir));
	if (t_near.x > t_near.y)
	{
		if (ray_dir.x < 0)
		{
			contact_normal = { 1, 0 };
		}
		else
		{
			contact_normal = { -1, 0 };
		}
	}
	else if (t_near.x < t_near.y)
	{
		if (ray_dir.y < 0)
		{
			contact_normal = { 0, 1 };
		}
		else
		{
			contact_normal = { 0, -1 };
		}
	}
	return true;
}

bool phys::DynamicRectVsRect(const sf::Vector2f& r1Pos, const sf::Vector2f& r1Size, const sf::Vector2f velIn, const sf::Vector2f& rTargetPos, const sf::Vector2f& rTargetSize, sf::Vector2i& contact_point, sf::Vector2i& contact_normal, float& contact_time, float fElapsedTime)
{
	if (velIn.x == 0 && velIn.y == 0)
	{
		return false;
	}
	sf::Vector2f expanded_targetPos;
	sf::Vector2f expanded_targetSize;
	expanded_targetPos = { rTargetPos.x - r1Size.x / 2.f , rTargetPos.y - r1Size.y / 2.f };
	expanded_targetSize = rTargetSize + r1Size;
	if (RayVsRect(r1Pos + r1Size / 2.f, velIn * fElapsedTime, expanded_targetPos, expanded_targetSize, contact_point, contact_normal, contact_time))
	{
		if (contact_time <= 1.0f && contact_time >= 0.f)
			return true;
	}
	return false;
}


