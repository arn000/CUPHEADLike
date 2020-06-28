#pragma once
#include "Window.h"
#include "timer.h"
class HpBarEnem {
	friend class Player;
	friend class Npc;
public:

	HpBarEnem(Window* win, int w, int h, int x, int y, int r, int g, int b, int a);
	void draw()const;
private:

	Window* window;
	int w_hp, h_hp;
	int x_hp, y_hp;
	int r_hp, g_hp, b_hp, a_hp;
};
