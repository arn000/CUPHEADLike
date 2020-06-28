#pragma once
#include <algorithm> 
#include "bullet.h"
#include "window.h"
#include "gameobj.h"
#include "wall.h"
#include "npc.h"
#include "timer.h"
#include "hpbarenemy.h"
#include "ultimate.h"
#include "mana.h"
#include "coin.h"
#include "text.h"
#include <vector>
#include "vector2d.h"
#include <array>
#include <map>
class game {
private:
	int score=0;
	Window* window_object;
	Npc* npc_object;
	//Collision* wall_object;
	int pts = 0;
	HpBarEnem* hpen_object;
	Mana* mana_object;
	Text* text_object;
	std::vector<Coin*>coins;
	std::vector<GameObject*>GameObjs;
	std::vector<Bullet*>bullets;
	std::vector<Collision*>walls;
	std::vector<Ultimate*>ultimates;


public:
	
	game();
	~game();
	void initialize();
};