#pragma once
#pragma once
#include "window.h"
class Player;
class Coin {
	friend class Collision;
	friend class Bullet;
	friend class Player;
public:

	Coin(Window* win, float w, float h, float x, float y, int r, int g, int b, int a);
	Coin(Window* win, float w, float h, float x, float y, const std::string& image_path);
	~Coin();
	void draw();
	bool CheckCollect(Player* player);
	int score(Player* player);
	int points = 0;
private:

	Window* window;
	float _w, _h;
	float _x, _y;
	int _r, _g, _b, _a;
	SDL_Texture* _char_texture = nullptr;
};