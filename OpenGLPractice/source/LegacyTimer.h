#ifndef _LEGACY_TIMER
#define _LEGACY_TIMER

#include <Windows.h>
#include <string>

class LegacyTimer
{
public:
	LegacyTimer();
	LegacyTimer(std::string a_Name);

	void StartTimer();

	//also executes tick timer
	void EndTimer();
	void PrintTimer();
	void TickTimer();

	std::string GetName();
	double GetTotalTime();
	double GetElapsedTime();

private:
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER frequency;

	double elapsedTime;
	double prevElapsedTime;
	double totalTime;
	std::string name;
};

#endif