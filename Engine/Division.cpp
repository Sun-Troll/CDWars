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

void Division::SetLines(bool more)
{
	if (more && nLines < 6)
	{
		++nLines;
	}
	else if (!more && nLines > 1)
	{
		--nLines;
	}
}

void Division::SetGear(bool more)
{
	if (more && gear < gtMax)
	{
		++gear;
	}
	else if (!more && gear > gtMin)
	{
		--gear;
	}
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
