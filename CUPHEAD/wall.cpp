#include "wall.h"
#include "gameobj.h"
#include <iostream>

Collision::Collision(Window* win, int w, int h, int x, int y, int r, int g, int b, int a) :
	window(win), w_wall(w), h_wall(h), x_wall(x), y_wall(y), r_wall(r), g_wall(g), b_wall(b), a_wall(a)
{

}

void Collision::draw() const {
	if (checkdraw) { 
		SDL_Rect wall;
		wall.w = w_wall;
		wall.h = h_wall;
		wall.x = x_wall;
		wall.y = y_wall;

		SDL_SetRenderDrawColor(window->getrenderer(), 130, 90, 44, 1);
		SDL_RenderFillRect(window->getrenderer(), &wall);
	}
}

bool Player::CheckColl(Collision& wall) const {

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = position.get_x();
	rightA = position.get_x() + size.get_x();
	topA = position.get_y();
	bottomA = position.get_y() + size.get_y();

	leftB = wall.x_wall;
	rightB = wall.x_wall + wall.w_wall;
	topB = wall.y_wall;
	bottomB = wall.y_wall + wall.h_wall;

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

bool Player::CheckCollEnemy(Npc& npc) {
	
	if ((position.get_x() >= npc._x && position.get_x() <= npc._x + npc._w) && (position.get_y() >= npc._y && position.get_y() <= npc._y + npc._h))
	{
		return false;
	}

	if ((position.get_x() + size.get_x() >= npc._x && position.get_x() + size.get_x() <= npc._x + npc._w) && (position.get_y() >= npc._y && position.get_y() <= npc._y + npc._h))
	{
		return false;
	}

	if ((position.get_x() >= npc._x && position.get_x() <= npc._x + npc._w) && (position.get_y() + size.get_y() >= npc._y && position.get_y() + size.get_y() <= npc._y + npc._h))
	{
		return false;
	}

	if ((position.get_x() + size.get_x() >= npc._x && position.get_x() + size.get_x() <= npc._x + npc._w) && (position.get_y() + size.get_y() >= npc._y && position.get_y() + size.get_y() <= npc._y + npc._h))
	{
		return false;
	}

	else
	{
		return true;
	}
	
}

