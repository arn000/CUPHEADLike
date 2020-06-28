#include "timer.h"
#include <SDL.h>

unsigned int Timer::m_OldTick;
unsigned int Timer::m_CurrentTick;
void Timer::UpdateTimer()
{
	m_OldTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();
}
float Timer::GetDT()
{
	float res = (m_CurrentTick - m_OldTick) * 1000.0f;
	if (res > 0.2f)
		res = 0.2f;
	return res;
}

