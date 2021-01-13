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
		Division::Unit unitsL, unsigned char nLinesL, unsigned char gearL, unsigned char trainingL,
		Division::Unit unitsC, unsigned char nLinesC, unsigned char gearC, unsigned char trainingC,
		Division::Unit unitsR, unsigned char nLinesR, unsigned char gearR, unsigned char trainingR,
		Division::Unit unitsB, unsigned char nLinesB, unsigned char gearB, unsigned char trainingB);
	void Move(float dt);
	bool Detect(const Army& enemy) const;
	void SetPos(const VecF& pos);
	void SetTarget(const VecF& trg);
	void SwitchState(State stNew);
	const VecF& GetPos() const;
	const VecF& GetTarget() const;
	float GetDetectRad() const;
	State GetState() const;
	//divisions
	void SetLines(unsigned char i, bool more);
	void SetGear(unsigned char i, bool more);
	Division::Unit GetUnits(int i) const;
	unsigned char GetLines(int i) const;
	unsigned char GetGear(int i) const;
	unsigned char GetTraining(int i) const;
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