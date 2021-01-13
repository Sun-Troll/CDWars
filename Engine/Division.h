#pragma once

class Division
{
public:
	enum class Unit : unsigned char
	{
		Knight,
		Archer
	};
public:
	Division(Division::Unit units_in, unsigned char nLines_in, unsigned char gear_in, unsigned char training_in);
	void SetLines(bool more);
	void SetGear(bool more);
	Unit GetUnits() const;
	unsigned char GetLines() const;
	unsigned char GetGear() const;
	unsigned char GetTraining() const;
	static unsigned char GetGtMin();
	static unsigned char GetGtMax();
private:
	static constexpr unsigned char gtMin = 10;
	static constexpr unsigned char gtMax = 99;
	Unit units;
	unsigned char nLines;
	unsigned char gear;
	unsigned char training;
	//ai
};