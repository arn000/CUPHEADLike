#include "game_manager.h"

game::game() {

}
game::~game() {

}
void pollEvents(Window& window, Player* player) {

	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		player->handledash(event);
		window.pollEvents(event);
	}
}

void game::initialize() {
	const Uint8* state = SDL_GetKeyboardState(NULL); 
	window_object = new Window("Cuphead", 800, 600);
	npc_object = new Npc(&window_object[0], 120.0f, 120.0f, 5.0f, 380.0f, "res/enemy.png");
	hpen_object = new HpBarEnem(&window_object[0], 300, 5, 450, 70, 170, 0, 255, 1);
	mana_object = new Mana(&window_object[0], 300, 5, 40, 100, 170, 0, 255, 1);
	walls.push_back(new Collision(&window_object[0], 800, 120, 0, 500, 130, 90, 44, 1));
	coins.push_back(new Coin(&window_object[0], 60.0f, 60.0f, 100.0f, 300.0f, "res/coin.png"));
	coins.push_back(new Coin(&window_object[0], 60.0f, 60.0f, 300.0f, 200.0f, "res/coin.png"));
	coins.push_back(new Coin(&window_object[0], 60.0f, 60.0f, 550.0f, 425.0f, "res/coin.png"));
	GameObjs.push_back(new Player(&window_object[0], Vector2D<float>(120.0f, 120.0f), Vector2D<float>(5.0f, 378.0f), "res/char.png",4,100)); 
	GameObjs.push_back(new HpBar(&window_object[0], Vector2D <float>(300.0f, 5.0f), Vector2D <float>(40.0f, 70.0f), 255, 0, 0, 1));
	text_object = new Text(Window::renderer, "res/arial.ttf", 30, std::to_string(score), { 0, 0, 0, 0 });

	while (!window_object[0].isClosed()) {
		pollEvents(window_object[0], dynamic_cast<Player*>(GameObjs[0]));
		auto collect_predicate = [&](Coin* coin) {
			if (coin->CheckCollect(dynamic_cast<Player*>(GameObjs[0]))) {
				delete coin;
				score++;
				delete text_object;
				text_object = new Text(Window::renderer, "res/arial.ttf", 30, std::to_string(score), { 0, 0, 0, 0 });
				return true;
			}
			return false;
		};
		coins.erase(std::remove_if(coins.begin(), coins.end(), collect_predicate), coins.end());

		for (size_t i = 0; i < coins.size(); i++) {
			coins[i]->draw();
		}
		for (size_t i = 0; i < walls.size(); i++) {
			dynamic_cast<Player*>(GameObjs[0])->movement(walls[i]);
			dynamic_cast<Player*>(GameObjs[0])->CheckColl(*walls[i]);
		}
		for (size_t i = 0; i < walls.size(); i++)
		{
			walls[i]->draw();
		}
		npc_object->movement(dynamic_cast<Player*>(GameObjs[0]));
		mana_object->draw();
		hpen_object->draw();
		npc_object->draw();
		text_object->display(390, 20, Window::renderer);

		for (size_t i = 0; i < GameObjs.size(); i++)
		{
			GameObjs[i]->draw();
		}

		if (state[SDL_SCANCODE_SPACE]) {
			if (Bullet::cooldown <= Bullet::silience) {
				if (!dynamic_cast<Player*>(GameObjs[0])->getFlip()) {
					bullets.push_back(new Bullet(&window_object[0], 30, 20, GameObjs[0]->getX() + 120, GameObjs[0]->getY() + 70, "res/bullet.png", 1));
				}
				if (dynamic_cast<Player*>(GameObjs[0])->getFlip()) {
					bullets.push_back(new Bullet(&window_object[0], 30, 20, GameObjs[0]->getX() + 90, GameObjs[0]->getY() + 70, "res/bullet.png", 0));
				}
				Bullet::silience = 0;
			}
		}
		Bullet::silience += Timer::GetDT();
		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			npc_object->EnemyHealth(bullets[i], hpen_object[0], &mana_object[0]);
			if (bullets[i]->isAlive)
			{
				bullets[i]->Update();
			}
			else
			{
				Bullet* temp = bullets[i];
				bullets.erase(bullets.begin() + i);
				delete temp;
			}
		}
		std::for_each(bullets.begin(), bullets.end(),
			[&](Bullet* bullet)
			{
				bullet->draw();
			}
		);
	
		//ULTIMATE
		if (state[SDL_SCANCODE_R]) {

			if (Ultimate::cooldown <= Ultimate::silience && (mana_object->getMana()==300 )) {
				if (!dynamic_cast<Player*>(GameObjs[0])->getFlip()) {
					ultimates.push_back(new Ultimate(&window_object[0], 150, 20, GameObjs[0]->getX() + 120, GameObjs[0]->getY() + 70, 0, 230, 64, 1,1));
				}
				if (dynamic_cast<Player*>(GameObjs[0])->getFlip()) {
					ultimates.push_back(new Ultimate(&window_object[0], 150, 20, GameObjs[0]->getX() + 120, GameObjs[0]->getY() + 70, 0, 230, 64, 1,0));
				}
				Ultimate::silience = 0;
			}
		}
		Ultimate::silience += Timer::GetDT();

		for (unsigned int i = 0; i < ultimates.size(); i++)
		{ 
			npc_object->UltimateDamage(ultimates[i], hpen_object[0]);
			if (ultimates[i]->isAlive)
			{
				ultimates[i]->Update();
			}
			else
			{
				Ultimate* temp = ultimates[i];
				ultimates.erase(ultimates.begin() + i);
				delete temp;
			}
		}
		for (unsigned int i = 0; i < ultimates.size(); i++)
		{
			ultimates[i]->draw();
		}

		dynamic_cast<Player*>(GameObjs[0])->CheckCollEnemy(npc_object[0]);
		dynamic_cast<Player*>(GameObjs[0])->PlayerHealth(&npc_object[0], dynamic_cast<HpBar*>(GameObjs[1]));
		dynamic_cast<Player*>(GameObjs[0])->PlayerMana(&mana_object[0]);
		window_object->clear();
		window_object->Update();
	}
	delete GameObjs[0];
	delete GameObjs[1];
	
	
}