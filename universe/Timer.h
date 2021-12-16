#pragma once

#include "sdl_includes.h"

typedef void (*TimerFinishedCb)(void* userdata);

class Timer
{
public:
	Timer() : m_ms(0u), m_startTick(0u), m_finishedTick(0u), m_cb(nullptr), m_started(false), m_finished(true) {}

	void Start(unsigned int ms)
	{
		m_ms = ms;
		m_started = true;
		m_finished = false;
		m_startTick = SDL_GetTicks();
		m_finishedTick = m_startTick + ms;
	}

	void Run(void* userdata)
	{
		if (!m_finished)
		{
			const bool countFinished = (m_finishedTick < SDL_GetTicks());

			if (countFinished)
			{
				if (m_cb)
				{
					m_cb(userdata);
				}

				m_finished = true;
			}
		}
	}

	bool IsStarted() const
	{
		return m_started;
	}

	bool IsFinished() const
	{
		return m_finished;
	}

	void SetFinishedCallback(TimerFinishedCb cb)
	{
		m_cb = cb;
	}

private:
	unsigned int m_ms;
	unsigned int m_startTick;
	unsigned int m_finishedTick;
	TimerFinishedCb m_cb;
	bool m_started;
	bool m_finished;
};