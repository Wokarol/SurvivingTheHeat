#pragma once

#include <SFML/Graphics.hpp>
#include <actors/components/settings/gunSettings.h>
#include <actor.h>

namespace wok
{
    class Gun
    {
    public:
        Gun() : settings(nullptr) {}
        Gun(ActorHandle<Actor> owner, GunSettings& settings, std::shared_ptr<sf::Texture> texture) :
            owner(owner), settings(&settings), texture(texture)
        {}

        void update(const sf::Transformable& body, sf::Vector2f aimTarget, GameClock time);
        void draw(sf::RenderTarget& target, sf::RenderStates& states);
        void loadAssets(sf::Vector2f bodyPivot);

    private:
        auto updateGunPositionAndRotation(const sf::Transformable& body, sf::Vector2f mousePosition)->std::pair<sf::Vector2f, float>;
        auto getGunRay(const sf::Transformable& body)->m::Ray;
        void updateShootingLogic(const sf::Transformable& body, sf::Vector2f globalGunPosition, m::Ray gunRay, const GameClock& time);
        void shoot(const sf::Transformable& body, sf::Vector2f globalGunPosition, m::Ray gunRay);

    private:
        ActorHandle<Actor> owner;
        GunSettings* settings;

        sf::Sprite gun;
        sf::Sprite muzzleFlash;

        std::shared_ptr<sf::Texture> texture;

        sf::Vector2f gunOffsetInRelationToPivot;

        bool shouldRenderMuzzleFlash = false;
        float shootCooldown = 0;
    };
};
