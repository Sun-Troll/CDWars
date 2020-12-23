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
	}
}

void Army::SetTarget(const VecF& trg)
{
	target = trg;
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
	return detectRad;
}
