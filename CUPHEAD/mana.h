#pragma once
#include "Window.h"
#include "timer.h"
class Mana {
	friend class Player;
	friend class Npc;
public:

	Mana(Window* win, int w, int h, int x, int y, int r, int g, int b, int a);
	void draw()const;
	int getMana();
private:

	Window* window;
	int w_mana, h_mana;
	int x_mana, y_mana;
	int r_mana, g_mana, b_mana, a_mana;
};
#pragma once
