#include "gameobj.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "wall.h"
#include "window.h"
#include "timer.h"

GameObject::GameObject(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a) :
	window(win), size(size), position(position), _r(r), _g(g), _b(b), _a(a) {
}
Char::Char(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a) :
	GameObject (win,size, position, r, g, b, a) {

}
Player::Player(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a) :
	Char (win, size, position, r, g, b, a)
{
	
	
}
GameObject:: ~GameObject() {

}

Char::Char(Window* win, Vector2D<float>size, Vector2D<float>position, const std::string &image_path) :
	GameObject(win,size,position,255, 0,0,255)
{
	
}

Player::Player(Window* win, Vector2D<float>size, Vector2D<float>position, const std::string& image_path, int nFrames, int mSpeed) :
	Char(win, size, position, image_path)
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

Player:: ~Player() {
	SDL_DestroyTexture(_char_texture);
}

void Player::draw() const{
	SDL_FRect player = { position.get_x(), position.get_y(), size.get_x(), size.get_y() };
	if (_char_texture) {
		SDL_RenderCopyExF(window->getrenderer(), _char_texture, nullptr, &player, angle, center, flip);
	}
	else {
		SDL_SetRenderDrawColor(window->getrenderer(), _r, _g, _b, _a);
		SDL_RenderFillRectF(window->getrenderer(), &player);
	}
	
}

void Player::movement(Collision *wall) {

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_D] ) {
		flip = SDL_FLIP_NONE;
		flipped = false;
	
		position = position + Vector2D<float>(0.5, 0);
		if (CheckColl(*wall)) {  //elseif
			position = position + Vector2D<float>(-0.5, 0);
		}
	}
	if (state[SDL_SCANCODE_A] ) {
		flip = SDL_FLIP_HORIZONTAL;
		flipped = true;
	
		position = position + Vector2D<float>(-0.5, 0);
		if (CheckColl(*wall)) {
			position = position + Vector2D<float>(0.5, 0);
		}
	}
	if (state[SDL_SCANCODE_W ] && falling == false) {
			jumping = true;
			curJumpForce = myJumpForce;
			
	}
	if (jumping) {
		if (curJumpForce < 0) {
			falling = true;
			}
		position = position + Vector2D<float>(0,curJumpForce * -Timer::GetDT());
			
			if (curJumpForce < maxFallSpeed) {
				myJumpForce -= myGravity * Timer::GetDT();
			}
			else {
				curJumpForce = maxFallSpeed;
			}
			if (position.get_y() < 100 ) {
				falling = true;
			}
			if (position.get_y() >= wall->y_wall - wall->h_wall-1) {
				jumping = false;
				falling = false;
		}	
	}
	if (state[SDL_SCANCODE_S]) {
		position = position + Vector2D<float>(0, 0.5);
		if (CheckColl(*wall)) {
			position = position + Vector2D<float>(0, -0.5);
		}
	}
	
}
void Player::handledash(SDL_Event& event) {
	
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_f:
			if (!flipped) {
				position = position + Vector2D<float>(Timer::GetDT() * 1500, 0);
			}
			if (flipped) {
				position = position + Vector2D<float>(Timer::GetDT() * -1500,0);
			}
			break;
		}
	}
}
float GameObject::getX() {
	return position.get_x();
}
float GameObject::getY() {
	return position.get_y();
}
bool Player::getFlip() {
	return flipped;
}
void Player::PlayerHealth(Npc* npc, HpBar* hp)
{
	if (!CheckCollEnemy(*npc) && CD <= invulnerability)
	{
		hp->size.set_x(hp->size.get_x() - 100);
		if (hp->size.get_x() == 0) {
			 window->_closed = true;
		}
		invulnerability = 0;
		//std::cerr << "works" << "\n";
	}
	invulnerability += Timer::GetDT();
}
void Player::PlayerMana(Mana* mana)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (mana->w_mana ==300 && state[SDL_SCANCODE_R])
	{
		mana->w_mana = mana->w_mana - 100;
		//std::cerr << "works" << "\n";
	}
	

}
