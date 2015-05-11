#ifndef _GAME_TIMER_H
#define _GAME_TIMER_H

#include "LegacyTimer.h"

class GameTimer
{
public:
	static GameTimer& Instance()
	{
		static GameTimer instance;
		return instance;
	}

	void StartTimer()
	{
		m_Timer.StartTimer();
	}

	void EndTimer()
	{
		m_Timer.EndTimer();
	}

	void PrintTimer()
	{
		m_Timer.PrintTimer();
	}

	double GetElapsedTime()
	{
		return m_Timer.GetElapsedTime();
	}

	double GetTotalTime()
	{
		return m_Timer.GetTotalTime();
	}
private:
	GameTimer()
	{
		m_Timer = LegacyTimer("GameTimer");
	}

	GameTimer(GameTimer const&) = delete;
	void operator=(GameTimer const&) = delete;

	LegacyTimer m_Timer;
};

#endif