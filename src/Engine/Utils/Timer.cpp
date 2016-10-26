#include "Timer.h"

using namespace Utils;

Timer::Timer()
	: mTime{std::chrono::high_resolution_clock::now()}
{
}


Timer::~Timer()
{
}

double Timer::getDelta()
{
	using namespace std::chrono;
	auto currentTime = high_resolution_clock::now();
	duration<double> delta{ currentTime - mTime };
	mTime = currentTime;
	return delta.count();
}
