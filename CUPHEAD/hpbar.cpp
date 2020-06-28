#include "gameobj.h"
#include <iostream>

HpBar::HpBar(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a) :
	GameObject(win,size, position, r, g, b, a)
{
}

void HpBar::draw() const {
		SDL_FRect hp;
		hp.w = size.get_x();
		hp.h = size.get_y();
		hp.x = position.get_x();
		hp.y = position.get_y();

		SDL_SetRenderDrawColor(window->getrenderer(), 255, 0, 0, 1);
		SDL_RenderFillRectF(window->getrenderer(), &hp);
}
