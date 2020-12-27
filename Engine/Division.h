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
private:
	Unit units;
	int nLines;
	int gear;
	int training;
	//ai
};