#pragma once
#include "window.h"
#include "bullet.h"

class Bullet {
	friend class Player;
	friend class Npc;
public:
	Bullet(Window* win, int w, int h, int x, int y, int r, int g, int b, int a);
	Bullet(Window* win, int w, int h, int x, int y, const std::string& image_path, bool dir);
	~Bullet();
	void draw();
	void Update();
	void setTexture(const std::string& image_path);
	bool fire = true;
	int max_distance = 800;
	bool isAlive;
	int distance;
	static int cooldown;
	static float silience;
private:

	Window* window;
	int w_bullet, h_bullet;
	int x_bullet, y_bullet;
	int _r, _g, _b, _a;
	bool direction = false;
	SDL_Texture* _char_texture = nullptr;

};

