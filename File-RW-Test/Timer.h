#pragma once
#include <chrono>
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> clock;

public:
	Timer() : clock(clock_t::now()) { }

	void reset() { clock = clock_t::now(); }

	double elapsed() const { return std::chrono::duration_cast<second_t>(clock_t::now() - clock).count(); }
};

