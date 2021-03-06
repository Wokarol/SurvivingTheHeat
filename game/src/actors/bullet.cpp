#include <actors/bullet.h>
#include <resources.h>
#include <utils/mathUtils.h>
#include <world.h>

wok::Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, Collideable::CollisionContext::SourceType bulletSource, std::shared_ptr<BulletSettings> settings) :
    settings(settings),
    direction(m::normalize(direction)), texture(res::get<sf::Texture>(settings->textureName)),
    bulletSource(bulletSource)
{
    setPosition(position);
    setRotation(m::angle(direction));

    setTexture(*texture);
    assetsReloaded();
}

void wok::Bullet::assetsReloaded()
{
    setTextureRect(settings->textureRect);
    setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f); // Centre
}

void wok::Bullet::update(const GameClock& time)
{
    timeSinceStart += time.delta;
    if (timeSinceStart > settings->lifespan)
    {
        handle.destroy();
        return;
    }

    float distanceDelta = settings->velocity * time.delta;

    Collideable::CollisionContext ctx(bulletSource);

    auto raycastResult = world::raycastAgainstHitboxes(ctx, m::Ray(getPosition(), direction), distanceDelta);
    if (raycastResult.collideable.isValid())
    {
        auto hitActor = raycastResult.collideable.as<Hittable>();

        if (hitActor.isValid())
        {
            hitActor->reactToHit(Hittable::HitData(direction, settings->damage));
        }
        handle.destroy();
    }

    move(direction * distanceDelta);
}

void wok::Bullet::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
    target.draw(*this, states);
}

void wok::Bullet::drawGizmos(sf::RenderTarget& target, sf::RenderStates& states)
{
    sf::CircleShape circle(1.f);
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin({ 1.f, 1.f });

    circle.setPosition(getPosition());

    target.draw(circle, states);
}
