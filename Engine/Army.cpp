#include "Army.h"

Army::Army(State st_in, const VecF& pos)
	:
	st(st_in),
	hitbox(pos, colRad)
{
	SwitchState(st_in);
}

void Army::Move(float dt)
{
	if (hitbox.center != target)
	{
		const VecF move = VecF{ target - hitbox.center }.GetNormalized() * speed * dt;
		if (VecF{ target - hitbox.center }.GetLengthSq() <= move.GetLengthSq())
		{
			hitbox.center = target;
		}
		else
		{
			hitbox.center += move;
		}
		detection.center = hitbox.center;
	}
}

bool Army::Detect(const Army& enemy) const
{
	return detection.Coliding(enemy.hitbox);
}

void Army::SetTarget(const VecF& trg)
{
	target = trg;
}

void Army::SwitchState(State stNew)
{
	switch (stNew)
	{
	case State::March:
		detection.radius = dMarch;
		speed = sMarch;
		hide = hMarch;
		st = State::March;
		break;
	case State::Scout:
		detection.radius = dScout;
		speed = sScout;
		hide = hScout;
		st = State::Scout;
		break;
	case State::Sneak:
		detection.radius = dSneak;
		speed = sSneak;
		hide = hSneak;
		st = State::Sneak;
		break;
	default:
		break;
	}
}

const VecF& Army::GetPos() const
{
	return hitbox.center;
}

const VecF& Army::GetTarget() const
{
	return target;
}

float Army::GetDetectRad() const
{
	return detection.radius;
}

Army::State Army::GetState() const
{
	return st;
}
