#include "Division.h"
#include <cassert>

Division::Division(Division::Unit units_in, int nLines_in, int gear_in, int training_in)
	:
	units(units_in),
	nLines(nLines_in),
	gear(gear_in),
	training(training_in)
{
	assert(nLines >= 1 && nLines <= 6);
	assert(gear >= gtMin && gear <= gtMax);
	assert(training >= gtMin && training <= gtMax);
}

Division::Unit Division::GetUnits() const
{
	return units;
}

int Division::GetLines() const
{
	return nLines;
}

int Division::GetGear() const
{
	return gear;
}

int Division::GetTraining() const
{
	return training;
}

int Division::GetGtMin()
{
	return gtMin;
}

int Division::GetGtMax()
{
	return gtMax;
}
