#pragma once
#include "window.h"
#include "wall.h"
#include "bullet.h"
#include "timer.h"
#include "hpbarenemy.h"
#include "mana.h"
#include "ultimate.h"
class Player;
class Npc {
	friend class Collision;
	friend class Bullet;
	friend class Player;
public:

	Npc(Window* win, float w, float h, float x, float y, int r, int g, int b, int a);
	Npc(Window* win, float w, float h, float x, float y, const std::string& image_path);
	~Npc();
	void draw() ;
	void movement(Player* player);
	bool CheckCollBullet(Bullet& bullet);
	bool CheckCollUltimate(Ultimate& ultimate);
	void EnemyHealth(Bullet* bullet, HpBarEnem& hpen, Mana* mana);
	void UltimateDamage(Ultimate* ultimate, HpBarEnem& hpen);
	float getX();
	float getY();
	bool right = false;
	static int DMGCD;
	static float INSHOT;
	bool falling = false;
	bool jumping = false;
	int lookaround = 250;
	float rethink = 1;
	float tempX = 0;
private:
	float myGravity = 2.0f;
	float maxFallSpeed = -3.0f;
	float myJumpForce = 5.0f;
	float curJumpForce = 0.0f;
	Window* window;
	float _w, _h;
	float _x, _y;
	int _r, _g, _b, _a;
	SDL_Texture* _char_texture = nullptr;
};