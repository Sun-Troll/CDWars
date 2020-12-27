#include "Division.h"
#include <cassert>

Division::Division(Division::Unit units_in, int nLines_in, int gear_in, int training_in)
	:
	units(units_in),
	nLines(nLines_in),
	gear(gear_in),
	training(training_in)
{
	assert(nLines > 0 && nLines <= 6);
	assert(gear > 0 && gear <= 100);
	assert(training > 0 && training <= 100);
}
