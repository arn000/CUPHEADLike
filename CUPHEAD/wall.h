#pragma once
#include "window.h"
#include "timer.h"
class Collision {
	friend class Player;
	friend class Npc;
public:

	Collision(Window* win, int w, int h, int x, int y, int r, int g, int b, int a);
	void draw()const;
private:

	Window *window;
	int w_wall, h_wall;
	int x_wall, y_wall;
	int r_wall, g_wall, b_wall, a_wall;
	bool checkdraw = true;
};

