#include "mana.h"
#include <iostream>

Mana::Mana(Window* win, int w, int h, int x, int y, int r, int g, int b, int a) :
	window(win), w_mana(w), h_mana(h), x_mana(x), y_mana(y), r_mana(r), g_mana(g), b_mana(b), a_mana(a)
{
}
void Mana::draw() const {
	SDL_Rect mana;
	mana.w = w_mana;
	mana.h = h_mana;
	mana.x = x_mana;
	mana.y = y_mana;

	SDL_SetRenderDrawColor(window->getrenderer(), 0, 0, 255, 1);
	SDL_RenderFillRect(window->getrenderer(), &mana);
}
int Mana::getMana() {
	return w_mana;
}