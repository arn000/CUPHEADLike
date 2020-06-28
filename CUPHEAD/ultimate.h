#pragma once
#include "Window.h"
#include "bullet.h"

class Ultimate {
	friend class Player;
	friend class Npc;
public:

	void draw();
	Ultimate(Window* win, int w, int h, int x, int y, int r, int g, int b, int a, bool dir);
	void Update();
	bool fire = true;
	int max_distance = 800;
	bool isAlive;

	int distance;
	static int cooldown;
	static float silience;
private:

	Window* window;
	int w_ultimate, h_ultimate;
	int x_ultimate, y_ultimate;
	int r_ultimate, g_ultimate, b_ultimate, a_ultimate;
	bool direction = false;
};

