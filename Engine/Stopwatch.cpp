#include "Stopwatch.h"

using namespace std::chrono;

Stopwatch::Stopwatch()
	:
	current(steady_clock::now())
{
}

float Stopwatch::Duration()
{
	const auto old = current;
	current = steady_clock::now();
	duration<float> dur = current - old;
	return dur.count();
}
