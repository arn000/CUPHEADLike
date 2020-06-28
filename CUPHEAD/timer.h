#pragma once
#include <SDL.h>
class Timer {
	friend class Window;
	static unsigned int m_OldTick;
	static unsigned int m_CurrentTick;
	static void UpdateTimer();
public:

	static float GetDT();
};