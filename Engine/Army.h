#pragma once
#include "Circ.h"
#include "Division.h"
#include <vector>

class Army
{
public:
	enum class State : unsigned char
	{
		March,
		Scout,
		Sneak
	};
public:
	Army(State st_in, const VecF& pos,
		Division::Unit unitsL, int nLinesL, int gearL, int trainingL,
		Division::Unit unitsC, int nLinesC, int gearC, int trainingC,
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
	//divisions
	void SetLines(int i, bool more);
	void SetGear(int i, bool more);
	Division::Unit GetUnits(int i) const;
	int GetLines(int i) const;
	int GetGear(int i) const;
	int GetTraining(int i) const;
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
	std::vector<Division> divisions;
};