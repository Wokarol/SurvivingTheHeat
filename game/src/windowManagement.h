#pragma once

#include <SFML/Graphics.hpp>
#include <console.h>
#include <world.h>
#include <input.h>

static void initializeBoilerplate()
{
	cs::HideConsole();
}

static sf::RenderWindow createWindow()
{
	auto settings = sf::ContextSettings::ContextSettings(0, 0, 8);
	return sf::RenderWindow(sf::VideoMode(25 * 32, 16 * 32), "Surviving The Heat", 7U, settings);
}

static void centreCamera(sf::RenderTarget& target)
{
	sf::View view(sf::Vector2f(0, 0), (sf::Vector2f)target.getSize());
	target.setView(view);
}

static void setCornerCam(sf::RenderTarget& target)
{
	sf::Vector2f targetSize = (sf::Vector2f)target.getSize();
	float ratio = targetSize.x / targetSize.y;

	float height = 16 * 16;
	float width = ratio * height;
	sf::View view = sf::View(sf::FloatRect(0, 0, width, height));
	target.setView(view);
}

static void handleDebugKeys(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::F10)
	{
		world::dumpActors();
	}
	if (event.key.code == sf::Keyboard::F3)
	{
		if (cs::IsConsoleVisible())
		{
			cs::HideConsole();
		}
		else
		{
			cs::ShowConsole();
		}
	}
}

static void handleEventsAndInput(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			handleDebugKeys(event);
			input::handleInputKeysPressed(event);
		}		
		if (event.type == sf::Event::KeyReleased)
		{
			input::handleInputKeysReleased(event);
		}
		if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i mousePos;
			mousePos.x = event.mouseMove.x;
			mousePos.y = event.mouseMove.y;
			input::mousePositionInWorld = window.mapPixelToCoords(mousePos);
		}
	}
}
