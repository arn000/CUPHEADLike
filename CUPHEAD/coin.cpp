#include "coin.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include"gameobj.h"

Coin::Coin(Window* win, float w, float h, float x, float y, int r, int g, int b, int a) :
	window(win), _w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a) {
}

Coin::Coin(Window* win, float w, float h, float x, float y, const std::string& image_path) :
	window(win), _w(w), _h(h), _x(x), _y(y), _r(255), _g(0), _b(0), _a(255)
{
	auto surface = IMG_Load(image_path.c_str());
	if (!surface)
	{
		std::cerr << "Failed to create surface \n";
	}
	_char_texture = SDL_CreateTextureFromSurface(window->getrenderer(), surface);
	if (!_char_texture) {
		std::cerr << "failed to create texture \n";
	}
	SDL_FreeSurface(surface);
}
Coin:: ~Coin() {
	SDL_DestroyTexture(_char_texture);
}

void Coin::draw() {
	SDL_FRect coin = { _x, _y, _w, _h };
	if (_char_texture) {
		SDL_RenderCopyF(window->getrenderer(), _char_texture, nullptr, &coin);
	}
	else {
		SDL_SetRenderDrawColor(window->getrenderer(), _r, _g, _b, _a);
		SDL_RenderFillRectF(window->getrenderer(), &coin);
	}
}
bool Coin::CheckCollect(Player* player) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = _x;
	rightA = _x + _w;
	topA = _y;
	bottomA = _y + _h;

	leftB = player->position.get_x();
	rightB = player->position.get_x() + player->size.get_x();
	topB = player->position.get_y();
	bottomB = player->position.get_y() + player->size.get_y();

	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}
	return true;

}
int Coin::score(Player* player) {
	if (CheckCollect(player)) {
		points++;
	}
	return points;
}