#pragma once

#include "sdl_includes.h"
#include <functional>

// typedef void (*TimerFinishedCb)(void* userdata);

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

	void SetFinishedCallback(std::function<void(void*)> cb)
	{
		m_cb = cb;
	}

	unsigned RemainingTicks()
	{
		if (!IsStarted() || (IsStarted() && IsFinished()))
			return 0u;

		const unsigned ticks = SDL_GetTicks();

		return m_finishedTick - ticks;
	}

private:
	unsigned m_ms;
	unsigned m_startTick;
	unsigned m_finishedTick;
	std::function<void(void*)> m_cb;
	bool m_started;
	bool m_finished;
};