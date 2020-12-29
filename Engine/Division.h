#pragma once

class Division
{
public:
	enum class Unit
	{
		Knight,
		Archer
	};
public:
	Division(Division::Unit units_in, int nLines_in, int gear_in, int training_in);
	Unit GetUnits() const;
	int GetLines() const;
	int GetGear() const;
	int GetTraining() const;
	static int GetGtMin();
	static int GetGtMax();
private:
	static constexpr int gtMin = 10;
	static constexpr int gtMax = 99;
	Unit units;
	int nLines;
	int gear;
	int training;
	//ai
};