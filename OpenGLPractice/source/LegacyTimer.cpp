#include "LegacyTimer.h"
#include <iostream>

LegacyTimer::LegacyTimer()
	: name("Default timer"),
	elapsedTime(0.0),
	prevElapsedTime(0.0),
	totalTime(0.0)
{
	QueryPerformanceFrequency(&frequency);
}

LegacyTimer::LegacyTimer(std::string a_Name)
	: name(a_Name),
	elapsedTime(0.0),
	prevElapsedTime(0.0),
	totalTime(0.0)
{
	QueryPerformanceFrequency(&frequency);
}

void LegacyTimer::StartTimer()
{
	QueryPerformanceCounter(&startTime);
}

void LegacyTimer::EndTimer()
{
	QueryPerformanceCounter(&endTime);
	TickTimer();
}

double LegacyTimer::GetTotalTime()
{
	return totalTime;
}

double LegacyTimer::GetElapsedTime()
{
	return elapsedTime;
}

void LegacyTimer::TickTimer()
{
	prevElapsedTime = elapsedTime;
	elapsedTime = ((double)(endTime.QuadPart - startTime.QuadPart) / (double)(frequency.QuadPart));
	totalTime += elapsedTime;
}

void LegacyTimer::PrintTimer()
{
	printf("Elapsed time for %s is %lf\n", name.c_str(), elapsedTime);
	printf("Total time for %s is %lf\n", name.c_str(), totalTime);
}

std::string LegacyTimer::GetName()
{
	return name;
}
