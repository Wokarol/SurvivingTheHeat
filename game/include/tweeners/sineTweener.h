#pragma once

#include <tweener.h>
#include <console.h>
#include <utils/mathUtils.h>

template <class T, typename Setter>
class SineTweener : public Tweener
{
	Setter setter;
	float elapsedTime = 0;
	float speed;
	T min, max;

public:
	SineTweener(Setter setter, T min, T max, float speed) :
		setter(setter),
		speed(speed),
		min(min), max(max)
	{}

	void addTimeOffset(float time)
	{
		elapsedTime += time;
	}

	virtual void tween(const GameClock& time) override
	{
		elapsedTime += time.delta * speed;

		float t = std::sin(elapsedTime) * 0.5f + 0.5f;

		setter(m::lerp(min, max, t));
	}
};
