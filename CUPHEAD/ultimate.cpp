#include "ultimate.h"
#include "window.h"
#include "gameobj.h"
int Ultimate::cooldown = 50;
float Ultimate::silience = 1;
Ultimate::Ultimate(Window* win, int w, int h, int x, int y, int r, int g, int b, int a, bool dir) :
	window(win), w_ultimate(w), h_ultimate(h), x_ultimate(x), y_ultimate(y), r_ultimate(r), g_ultimate(g), b_ultimate(b), a_ultimate(a), direction(dir)
{
	isAlive = true;
	distance = 0;
}
void Ultimate::draw() {
	SDL_Rect ultimate;
	ultimate.w = w_ultimate;
	ultimate.h = h_ultimate;
	ultimate.x = x_ultimate;
	ultimate.y = y_ultimate;

	SDL_SetRenderDrawColor(window->getrenderer(), 170, 0, 255, 1);
	SDL_RenderFillRect(window->getrenderer(), &ultimate);
}
void Ultimate::Update()
{
	if (max_distance < distance) {
		isAlive = false;
	}
	if (direction) {
		x_ultimate += 1;
		distance += 1;
	}
	if (!direction) {
		x_ultimate -= 1;
		distance -= 1;
	}
}