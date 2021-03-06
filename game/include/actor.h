#pragma once

#include <actorSystem/actorInterfaces.h>
#include <actorSystem/actorHandle.h>
#include <actorSystem/group.h>
#include <string>
#include <console.h>
#include <gameClock.h>

namespace wok
{
    class world;

    class Actor
    {
    public:
        std::shared_ptr<Group> group;
        std::string name;

        virtual void start(const GameClock&) {};
        virtual void drawGizmos(sf::RenderTarget&, sf::RenderStates&) {};
        virtual void assetsReloaded() {};
        virtual ~Actor() = default;
        ActorHandle<> getHandle() { return handle; }

        Actor& withGroup(std::shared_ptr<Group> g)
        {
            group = g;
            return *this;
        }

    protected:
        ActorHandle<> handle;

        friend world;
    };

    class Actor2D : public Actor
    {
    public:
        virtual sf::Vector2f getActorPosition() = 0;
    };
}
