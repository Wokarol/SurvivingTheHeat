#pragma once

#include <mathUtils.h>
#include <SFML/Graphics.hpp>

#include <console.h>

namespace inter
{
	struct Intersection
	{
		bool hit;
		float dist;
		sf::Vector2f normal;

		Intersection() : hit(false), dist(0), normal(sf::Vector2f(0.f, 0.f)) {}
		Intersection(float d, sf::Vector2f n) : hit(true), dist(d), normal(n) {}
	};

	/// <param name="AABB"> Rectangle has to be AABB </param>
	inline Intersection rayAABB(m::Ray ray, const sf::RectangleShape& aabb)
	{
		auto localOrigin = ray.origin + aabb.getOrigin();
		auto nDir = m::normalize(ray.dir);
		auto size = aabb.getSize();

		if (nDir.x > 0 && localOrigin.x < 0)
		{
			// Ray from left onto left wall
			float diff = -localOrigin.x;
			float distanceToWall = diff / nDir.x;
			float yOnWall = nDir.y * distanceToWall + localOrigin.y;

			if (yOnWall >= 0 && yOnWall <= size.y)
			{
				return Intersection(distanceToWall, sf::Vector2f(-1.f, 0.f));
			}
		}

		if (nDir.x < 0 && localOrigin.x > size.x)
		{
			// Ray from right onto right wall
			float diff = localOrigin.x - size.x;
			float distanceToWall = -diff / nDir.x;
			float yOnWall = nDir.y * distanceToWall + localOrigin.y;

			if (yOnWall >= 0 && yOnWall <= size.y)
			{
				return Intersection(distanceToWall, sf::Vector2f(1.f, 0.f));
			}
		}

		if (nDir.y > 0 && localOrigin.y < 0)
		{
			// Ray from up onto upper wall
			float diff = -localOrigin.y;
			float distanceToWall = diff / nDir.y;
			float xOnWall = nDir.x * distanceToWall + localOrigin.x;

			if (xOnWall >= 0 && xOnWall <= size.x)
			{
				return Intersection(distanceToWall, sf::Vector2f(0.f, -1.f));
			}
		}

		if (nDir.y < 0 && localOrigin.y > size.y)
		{
			// Ray from right onto right wall
			float diff = localOrigin.y - size.y;
			float distanceToWall = -diff / nDir.y;
			float xOnWall = nDir.x * distanceToWall + localOrigin.x;

			if (xOnWall >= 0 && xOnWall <= size.x)
			{
				return Intersection(distanceToWall, sf::Vector2f(0.f, 1.f));
			}
		}

		return {};
	}

	inline Intersection rayOBB(m::Ray ray, const sf::RectangleShape& obb)
	{
		ray.move(-obb.getPosition());

		auto angle = -obb.getRotation();
		ray.rotateAround(sf::Vector2f(0, 0), angle);

		auto res = rayAABB(ray, obb);
		res.normal = m::rotate(res.normal, -angle);

		return res;
	}
}