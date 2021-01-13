#include "Division.h"
#include <cassert>

Division::Division(Division::Unit units_in, unsigned char nLines_in, unsigned char gear_in, unsigned char training_in)
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

unsigned char Division::GetLines() const
{
	return nLines;
}

unsigned char Division::GetGear() const
{
	return gear;
}

unsigned char Division::GetTraining() const
{
	return training;
}

unsigned char Division::GetGtMin()
{
	return gtMin;
}

unsigned char Division::GetGtMax()
{
	return gtMax;
}
