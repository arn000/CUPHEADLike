#include "hpbarenemy.h"
#include <iostream>

HpBarEnem::HpBarEnem(Window* win, int w, int h, int x, int y, int r, int g, int b, int a) :
	window(win), w_hp(w), h_hp(h), x_hp(x), y_hp(y), r_hp(r), g_hp(g), b_hp(b), a_hp(a)
{
}
void HpBarEnem::draw() const {
	SDL_Rect hpen;
	hpen.w = w_hp;
	hpen.h = h_hp;
	hpen.x = x_hp;
	hpen.y = y_hp;

	SDL_SetRenderDrawColor(window->getrenderer(), 170, 0, 255, 1);
	SDL_RenderFillRect(window->getrenderer(), &hpen);
}
