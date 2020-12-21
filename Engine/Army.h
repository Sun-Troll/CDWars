#pragma once
#include "Circ.h"

class Army
{
public:
	enum class State
	{
		March,
		Scout,
		Sneak
	};
public:
	void Move(float dt);
	void SetTarget(const VecF& trg);
	const VecF& GetPos() const;
	const VecF& GetTarget() const;
private:
	static constexpr float colRad = 16.0f;
	static constexpr float dMarch = 1024.0f;
	static constexpr float dScout = dMarch * 2.0f;
	static constexpr float dSneak = dMarch * 0.5f;
	static constexpr float sMarch = 100.0f;
	static constexpr float sScout = sMarch * 0.5f;
	static constexpr float sSneak = sMarch * 0.5f;
	State st = State::March;
	CircF hitbox{ {0.0f, 8000.0f}, colRad };
	CircF detection{ hitbox.center, dMarch };
	VecF target = hitbox.center;
	float speed = sMarch;
};