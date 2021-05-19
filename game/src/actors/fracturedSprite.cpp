#include <actors/fracturedSprite.h>

#include <utils/mathUtils.h>

wok::FracturedSprite::FracturedSprite(const sf::Sprite& original, std::shared_ptr<sf::Texture> texture, std::vector<sf::IntRect> rects, float direction) :
	texture(texture)
{
	sf::Vector2f spritePos = original.getPosition();
	sf::Vector2f spriteOrigin = original.getOrigin();
	float rotation = original.getRotation();

	sf::IntRect spriteRect = original.getTextureRect();
	sf::Vector2i spriteRectPos = sf::Vector2i(spriteRect.left, spriteRect.top);

	yPos = spritePos.y;

	sf::Vector2i originalInTextureSpace = spriteRectPos + (sf::Vector2i)spriteOrigin;

	for (auto& rect : rects)
	{
		sf::Vector2i rectPos = { rect.left, rect.top };

		sf::Sprite fracture(*texture, rect);
		fracture.setOrigin(rect.width / 2, rect.height / 2);

		sf::Vector2i fractureInTextureSpace = rectPos + (sf::Vector2i)fracture.getOrigin();

		sf::Vector2i differenceOnTexture = fractureInTextureSpace - originalInTextureSpace;

		sf::Vector2f pos;
		pos += spritePos;
		pos += m::rotate((sf::Vector2f)differenceOnTexture, rotation);

		fracture.setPosition(pos);
		fracture.setRotation(rotation);

		// Point right-ish
		sf::Vector2f randomDirection = m::rotate(sf::Vector2f(70, 0), m::lerp(-30, -50, rand() / (float)RAND_MAX));
		randomDirection.x *= direction;

		fractures.emplace_back(
			fracture, 
			randomDirection,
			direction * m::lerp(120, 240, rand() / (float)RAND_MAX),
			m::lerp(1.3f, 1.6f, rand() / (float)RAND_MAX));
	}
}

void wok::FracturedSprite::update(const GameClock& time)
{
	bool anyLives = false;
	for (auto& fract : fractures)
	{
		fract.velocity += sf::Vector2f(0, 230) * time.delta;
		fract.lifetime -= fract.lifetimeDropRate * time.delta;

		if (fract.lifetime > 0)
		{
			fract.sprite.move(fract.velocity * time.delta);
			fract.sprite.rotate(fract.angularVelocity * time.delta);
			float scale = -std::pow(1.f - fract.lifetime, 2) + 1.f;
			fract.sprite.setScale(scale, scale);
			anyLives = true;
		}
		else
		{
			fract.sprite.setScale(0, 0);
		}
	}

	if (!anyLives)
	{
		handle.destroy();
	}

}

void wok::FracturedSprite::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	for (auto& fract : fractures)
	{
		target.draw(fract.sprite, states);
	}
}