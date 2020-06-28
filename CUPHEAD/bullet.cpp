#include "bullet.h"
#include "window.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "exception.h"
int Bullet::cooldown = 50;
float Bullet::silience = 1;

Bullet::Bullet(Window* win, int w, int h, int x, int y, int r, int g, int b, int a) :
	window(win), w_bullet(w), h_bullet(h), x_bullet(x), y_bullet(y), _r(r), _g(g), _b(b), _a(a)
{
	isAlive = true;
	distance = 0;
}
Bullet::Bullet(Window* win, int w, int h, int x, int y, const std::string& image_path, bool dir) :
	window(win), w_bullet(w), h_bullet(h), x_bullet(x), y_bullet(y), _r(255), _g(0), _b(0), _a(255), direction(dir)
{
	isAlive = true;
	distance = 0;
	
	try {
		setTexture(image_path);
	}
	catch (exceptions msg) {
		std::cerr << msg << std::endl;
	}
	
}
Bullet:: ~Bullet() {
	SDL_DestroyTexture(_char_texture);
}
void Bullet::setTexture(const std::string& image_path) {
	auto surface = IMG_Load(image_path.c_str());
	if (!surface)
	{
		throw exceptions(image_path + " : surface error.");
		//std::cerr << "Failed to create surface \n";
	}
	_char_texture = SDL_CreateTextureFromSurface(window->getrenderer(), surface);
	if (!_char_texture) {
		throw exceptions(image_path + " : texture error.");
		//std::cerr << "failed to create texture \n";
	}
	SDL_FreeSurface(surface);
}
void Bullet::draw() {
	SDL_Rect bullet = { x_bullet, y_bullet, w_bullet, h_bullet };
	if (_char_texture) {
		SDL_RenderCopy(window->getrenderer(), _char_texture, nullptr, &bullet);
	}
	else {
		SDL_SetRenderDrawColor(window->getrenderer(), _r, _g, _b, _a);
		SDL_RenderFillRect(window->getrenderer(), &bullet);
	}
}
void Bullet::Update()
{
	
	if (max_distance < distance) {
		isAlive = false;
	}
	if (direction) {
		x_bullet += 1;
		distance += 1;
	}
	else if (!direction) {
		x_bullet -= 1;
		distance -= 1;
	}
}
