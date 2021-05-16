#include <actors/debugPopup.h>
#include <assets/fonts.h>
#include <world.h>
#include <tweeners.h>
#include <memory>

auto color = 0xb03a2000;
std::vector<DebugPopup*> popusActive;


DebugPopup::DebugPopup(std::string message)
{
	text.setString(message);
	font = fonts::get("RobotoMono");

	text.setFont(*font);
	text.setColor(sf::Color(color + 0xff));
	text.setCharacterSize(8 * 2);
	text.setScale(0.5f, 0.5f);


	popusActive.push_back(this);
}

void DebugPopup::start()
{
	auto fadeOut = std::make_shared<LerpTweener<sf::Color>>(handle,
		[this]() { return text.getColor(); }, [this](auto v) { return text.setColor(v); },
		sf::Color(color), 2.f
		);

	auto myHandle = handle;
	fadeOut->getAfterKilled([myHandle]() {
		myHandle.destroy();
	});

	world::addTween(fadeOut);
}

void DebugPopup::update(const GameClock& time)
{
	auto it = std::find(popusActive.begin(), popusActive.end(), this);
	int pos = it - popusActive.begin();

	if (lastPos == -1)
	{
		text.setPosition(5.f, 5.f + pos * 10);
	}
	else if (lastPos != pos)
	{
		auto slide = std::make_shared<LerpTweener<sf::Vector2f>>(handle,
			[this]() { 
				return text.getPosition(); 
			}, 
			[this](auto v) { 
				return text.setPosition(v); 
			},
			sf::Vector2f(5.f, 5.f + pos * 10), 0.5f
		);
		world::addTween(slide);
	}
	lastPos = pos;
}

void DebugPopup::draw(sf::RenderTarget& target)
{
	target.draw(text);
}

DebugPopup::~DebugPopup()
{
	popusActive.erase(std::find(popusActive.begin(), popusActive.end(), this));
}