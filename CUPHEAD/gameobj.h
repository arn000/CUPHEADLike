#include "window.h"
#include "wall.h"
#include "bullet.h"
#include "timer.h"
#include "npc.h"
#include "mana.h"
#include "vector2d.h"
class Npc;
class GameObject {
public:

	GameObject(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a);
	//GameObject(Window* win, int w, int h, int x, int y);
	virtual ~GameObject();
	virtual void draw() const = 0;
	float getX();
	float getY();
	public:
	Window* window;
	Vector2D<float>size;
	Vector2D<float>position;
	int _r, _g, _b, _a;
};

class HpBar : public GameObject {
	friend class Player;
	friend class Npc;
public:

	HpBar(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a); //2 parameters
	void draw()const;
};

class Char: public GameObject {
public:

	Char(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a);
	Char(Window* win, Vector2D<float>size, Vector2D<float>position, const std::string& image_path);
	int normal = 0;
	SDL_Texture* _char_texture = nullptr;
private:
	
};

class Player : public Char{
	friend Char;
	friend class Collision;
	friend class Bullet;
	friend class Npc;
public:
	
	Player() = default;
	Player(Window* win, Vector2D<float>size, Vector2D<float>position, int r, int g, int b, int a);
	Player(Window* win, Vector2D<float>size, Vector2D<float>position, const std::string& image_path, int nFrames, int mSpeed);
	~Player();
	void draw() const;
	bool CheckColl(Collision& wall) const; 
	bool CheckCollEnemy(Npc& npc);
	virtual void movement(Collision* wall);
	void PlayerHealth(Npc* npc, HpBar* hp);
	void PlayerMana(Mana* mana);
	void handledash(SDL_Event& event);
	bool getFlip();
	bool falling = false;
	bool jumping = false;
	bool flipped = false;
	bool firing = true;
	bool dashing = false;
	double angle = 0.0;
	SDL_FPoint* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
private:

	bool animated = false;
	int frames = 0;
	int speed = 100;
	float myGravity = 2.0f;
	float maxFallSpeed = -3.0f;
	float myJumpForce = 5.0f;
	float curJumpForce = 0.0f;
	int CD = 250;
	float invulnerability = 1;
};

