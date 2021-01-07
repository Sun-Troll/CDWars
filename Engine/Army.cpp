#include "Army.h"

Army::Army(State st_in, const VecF& pos,
	Division::Unit unitsL, int nLinesL, int gearL, int trainingL,
	Division::Unit unitsC, int nLinesC, int gearC, int trainingC,
	Division::Unit unitsR, int nLinesR, int gearR, int trainingR,
	Division::Unit unitsB, int nLinesB, int gearB, int trainingB)
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

void Army::SetLines(int i, bool more)
{
	divisions[i].SetLines(more);
}

void Army::SetGear(int i, bool more)
{
	divisions[i].SetGear(more);
}

Division::Unit Army::GetUnits(int i) const
{
	return divisions[i].GetUnits();
}

int Army::GetLines(int i) const
{
	return divisions[i].GetLines();
}

int Army::GetGear(int i) const
{
	return divisions[i].GetGear();
}

int Army::GetTraining(int i) const
{
	return divisions[i].GetTraining();
}
