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
	Army(State st_in, const VecF& pos);
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
	State st;
	CircF hitbox;
	CircF detection{ hitbox.center, dMarch };
	VecF target = hitbox.center;
	float speed = sMarch;
};