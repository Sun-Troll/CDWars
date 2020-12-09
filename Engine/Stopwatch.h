#pragma once

#include <chrono>

class Stopwatch
{
public:
	Stopwatch();
	float Duration();
private:
	std::chrono::steady_clock::time_point current;
};