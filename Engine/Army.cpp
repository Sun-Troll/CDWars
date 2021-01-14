#include "Army.h"

Army::Army(State st_in, const VecF& pos,
	Division::Unit unitsL, unsigned char nLinesL, unsigned char gearL, unsigned char trainingL,
	Division::Unit unitsC, unsigned char nLinesC, unsigned char gearC, unsigned char trainingC,
	Division::Unit unitsR, unsigned char nLinesR, unsigned char gearR, unsigned char trainingR,
	Division::Unit unitsB, unsigned char nLinesB, unsigned char gearB, unsigned char trainingB)
	:
	hitbox(pos, colRad)
{
	divisions.reserve(4);
	divisions.emplace_back(unitsL, nLinesL, gearL, trainingL);
	divisions.emplace_back(unitsC, nLinesC, gearC, trainingC);
	divisions.emplace_back(unitsR, nLinesR, gearR, trainingR);
	divisions.emplace_back(unitsB, nLinesB, gearB, trainingB);
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
	CircF effDetect = detection;
	effDetect.radius *= enemy.hide;
	return effDetect.Coliding(enemy.hitbox);
}

void Army::SetPos(const VecF& pos)
{
	hitbox.center = pos;
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

void Army::SetLines(unsigned char i, bool more)
{
	divisions[i].SetLines(more);
}

void Army::SetGear(unsigned char i, bool more)
{
	divisions[i].SetGear(more);
}

Division::Unit Army::GetUnits(int i) const
{
	return divisions[i].GetUnits();
}

unsigned char Army::GetLines(int i) const
{
	return divisions[i].GetLines();
}

unsigned char Army::GetGear(int i) const
{
	return divisions[i].GetGear();
}

unsigned char Army::GetTraining(int i) const
{
	return divisions[i].GetTraining();
}
