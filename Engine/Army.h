#pragma once
#include "Circ.h"
#include "Division.h"

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
	Army(State st_in, const VecF& pos,
		Division::Unit unitsC, int nLinesC, int gearC, int trainingC,
		Division::Unit unitsL, int nLinesL, int gearL, int trainingL,
		Division::Unit unitsR, int nLinesR, int gearR, int trainingR,
		Division::Unit unitsB, int nLinesB, int gearB, int trainingB);
	void Move(float dt);
	bool Detect(const Army& enemy) const;
	void SetTarget(const VecF& trg);
	void SwitchState(State stNew);
	const VecF& GetPos() const;
	const VecF& GetTarget() const;
	float GetDetectRad() const;
	State GetState() const;
private:
	static constexpr float colRad = 16.0f;
	static constexpr float dMarch = 1024.0f;
	static constexpr float dScout = dMarch * 2.0f;
	static constexpr float dSneak = dMarch;
	static constexpr float sMarch = 100.0f;
	static constexpr float sScout = sMarch * 0.5f;
	static constexpr float sSneak = sMarch * 0.5f;
	static constexpr float hMarch = 1.0f;
	static constexpr float hScout = 1.0f;
	static constexpr float hSneak = 0.5f;
	State st;
	CircF hitbox;
	CircF detection{ hitbox.center, dMarch };
	VecF target = hitbox.center;
	float speed = sMarch;
	float hide = hMarch;
	Division center;
	Division left;
	Division right;
	Division back;
};