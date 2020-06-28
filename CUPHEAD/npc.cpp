#include "npc.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "gameobj.h"
#include <math.h>
int Npc::DMGCD = 50;
float Npc::INSHOT = 1;

Npc::Npc(Window* win, float w, float h, float x, float y, int r, int g, int b, int a) :
	window(win), _w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a) {
}

Npc::Npc(Window* win, float w, float h, float x, float y, const std::string& image_path) :
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


Npc:: ~Npc() {
	SDL_DestroyTexture(_char_texture);
}

void Npc::draw()  {
	SDL_FRect npc = { _x, _y, _w, _h };
	if (_char_texture) {
		SDL_RenderCopyF(window->getrenderer(), _char_texture, nullptr, &npc);
	}
	else {
		SDL_SetRenderDrawColor(window->getrenderer(), _r, _g, _b, _a);
		SDL_RenderFillRectF(window->getrenderer(), &npc);
	}
}

void Npc::movement(Player* player) {
	float dirx = player->position.get_x() - _x;
	float diry = player->position.get_y() - _y;
	float hyp = sqrt((dirx * dirx) + (diry * diry));
	_y += Timer::GetDT() *2 *(diry / hyp);
	_x += Timer::GetDT() * 1 * (dirx / hyp);
	if (_y < 380) {
		_y += Timer::GetDT() * 1;
	}
}

float Npc::getX() {
	return _x;
}
float Npc::getY() {
	return _y;
}

bool Npc::CheckCollBullet(Bullet& bullet) {
	/*
	if ((bullet.x_bullet >= _x && bullet.x_bullet <= _x + _w) && (bullet.y_bullet >= _y && bullet.y_bullet <= _y + _h))
	{
		return false;
	}
	if ((bullet.x_bullet + bullet.w_bullet >= _x && bullet.x_bullet + bullet.w_bullet <= _x + _w) && (bullet.y_bullet >= _y && bullet.y_bullet <= _y + _h))
	{
		return false;
	}
	if ((bullet.x_bullet >= _x && bullet.x_bullet <= _x + _w) && (bullet.y_bullet + bullet.x_bullet >=_y && bullet.y_bullet + bullet.h_bullet <= _y + _h))
	{
		return false;
	}
	if ((bullet.x_bullet + bullet.w_bullet >= _x && bullet.x_bullet + bullet.w_bullet <= _x + _w) && (bullet.y_bullet + bullet.h_bullet >= _y && bullet.y_bullet + bullet.h_bullet <= _y + _h))
	{
		return false;
	}
	else
	{
		return true;
	}
	*/

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = _x;
	rightA = _x + _w;
	topA = _y;
	bottomA = _y + _h;

	leftB = bullet.x_bullet;
	rightB = bullet.x_bullet + bullet.w_bullet;
	topB = bullet.y_bullet;
	bottomB = bullet.y_bullet + bullet.h_bullet;
	
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
bool Npc::CheckCollUltimate(Ultimate& ultimate) {
	/*
	if ((bullet.x_bullet >= _x && bullet.x_bullet <= _x + _w) && (bullet.y_bullet >= _y && bullet.y_bullet <= _y + _h))
	{
		return false;
	}
	if ((bullet.x_bullet + bullet.w_bullet >= _x && bullet.x_bullet + bullet.w_bullet <= _x + _w) && (bullet.y_bullet >= _y && bullet.y_bullet <= _y + _h))
	{
		return false;
	}
	if ((bullet.x_bullet >= _x && bullet.x_bullet <= _x + _w) && (bullet.y_bullet + bullet.x_bullet >=_y && bullet.y_bullet + bullet.h_bullet <= _y + _h))
	{
		return false;
	}
	if ((bullet.x_bullet + bullet.w_bullet >= _x && bullet.x_bullet + bullet.w_bullet <= _x + _w) && (bullet.y_bullet + bullet.h_bullet >= _y && bullet.y_bullet + bullet.h_bullet <= _y + _h))
	{
		return false;
	}
	else
	{
		return true;
	}
	*/

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = _x;
	rightA = _x + _w;
	topA = _y;
	bottomA = _y + _h;

	leftB = ultimate.x_ultimate;
	rightB = ultimate.x_ultimate + ultimate.w_ultimate;
	topB = ultimate.y_ultimate;
	bottomB = ultimate.y_ultimate + ultimate.h_ultimate;

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
void Npc::EnemyHealth(Bullet* bullet, HpBarEnem& hpen, Mana* mana)
{
	if (CheckCollBullet(*bullet) && DMGCD <= INSHOT)
	{
		hpen.w_hp = hpen.w_hp - 5;
		if(mana->w_mana <300)
		mana->w_mana = mana->w_mana + 10;
		if (hpen.w_hp <= 0) {
			window->_closed = true;
		}
		INSHOT = 0;
	}
	
	INSHOT += Timer::GetDT();
}
void Npc::UltimateDamage(Ultimate* ultimate, HpBarEnem& hpen)
{
	if (CheckCollUltimate(*ultimate) && DMGCD <= INSHOT)
	{
		hpen.w_hp = hpen.w_hp - 25;
	
		if (hpen.w_hp <= 0) {
			window->_closed = true;
		}
		INSHOT = 0;
	}
	INSHOT += Timer::GetDT();
}
