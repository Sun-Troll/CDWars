#include "Army.h"

Army::Army(State st_in, const VecF& pos)
	:
	st(st_in),
	hitbox(pos, colRad)
{
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

void Army::SetTarget(const VecF& trg)
{
	target = trg;
}

void Army::SwitchState(bool changed, State stNew)
{
	if (changed)
	{
		switch (stNew)
		{
		case Army::State::March:
			break;
		case Army::State::Scout:
			break;
		case Army::State::Sneak:
			break;
		default:
			break;
		}
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
