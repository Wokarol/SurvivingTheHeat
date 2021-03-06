#pragma once

#include <SFML/Graphics.hpp>
#include <actors/components/settings/gunSettings.h>
#include <actor.h>

namespace wok
{
    class Gun
    {
    public:
        Gun() : settings(nullptr), sourceType(Collideable::CollisionContext::SourceType::NONE) {}
        Gun(ActorHandle<> owner, wok::Collideable::CollisionContext::SourceType sourceType, GunSettings& settings, std::shared_ptr<sf::Texture> texture) :
            owner(owner), sourceType(sourceType), settings(&settings), texture(texture)
        {}

        void update(sf::Vector2f bodyPos, sf::Vector2f bodyScale, sf::Vector2f aimTarget, GameClock time);
        void tryToShoot();
        void draw(sf::RenderTarget& target, sf::RenderStates& states);
        void loadAssets(sf::Vector2f bodyPivot);

        sf::Vector2f getPosition() { return gun.getPosition(); }

    private:
        auto updateGunPositionAndRotation(sf::Vector2f bodyPos, sf::Vector2f bodyScale, sf::Vector2f mousePosition)->std::pair<sf::Vector2f, float>;
        auto getGunRay(sf::Vector2f bodyScale)->m::Ray;
        void shoot(sf::Vector2f bodyScale, sf::Vector2f globalGunPosition, m::Ray gunRay);

    private:
        ActorHandle<> owner;
        wok::Collideable::CollisionContext::SourceType sourceType;
        GunSettings* settings;

        sf::Sprite gun;
        sf::Sprite muzzleFlash;

        std::shared_ptr<sf::Texture> texture;

        sf::Vector2f gunOffsetInRelationToPivot;

        bool shouldRenderMuzzleFlash = false;
        float shootCooldown = 0;
    };
};
